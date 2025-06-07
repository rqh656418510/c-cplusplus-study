#include <arpa/inet.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <atomic>
#include <chrono>
#include <ctime>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "group.hpp"
#include "groupmodel.hpp"
#include "json.hpp"
#include "offlinemessage.hpp"
#include "offlinemessagemodel.hpp"
#include "public.hpp"
#include "times.hpp"
#include "user.hpp"
#include "usermodel.hpp"

using namespace std;

// 类型重定义
using json = nlohmann::json;

// 记录当前登录用户的基本信息
User g_currentUser;
// 记录当前登录用户的好友列表信息
vector<User> g_currentUserFriendList;
// 记录当前登录用户的群组列表信息
vector<Group> g_currentUserGroupList;

// 用于读/写线程之间的通信
sem_t rwsem;
// 控制主菜单程序运行
bool isMainMenuRunning = false;
// 记录用户的登录状态
atomic_bool g_isLoginSuccess{false};

// 主菜单程序
void mainMenu(int);
// 子线程接收到消息后的处理逻辑
void readTaskHandler(int clientfd);

// 显示当前登录用户的基本信息
void showCurrentUserData();

/////////////////////////////////////////////////////首页功能/////////////////////////////////////////////////////

// 聊天客户端程序实现, 主线程用作消息发送线程, 子线程用作消息接收线程
int main(int argc, char **argv) {
    if (argc < 3) {
        cerr << "command invalid, example: ./chat_client 127.0.0.1 6000" << endl;
        exit(-1);
    }

    // 解析通过命令行参数传递的IP和端口号
    char *ip = argv[1];
    uint16_t port = atoi(argv[2]);

    // 创建client端的socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == clientfd) {
        cerr << "socket create failed" << endl;
        exit(-1);
    }

    // 填写client需要连接的服务器信息（IP和端口号）
    sockaddr_in server;
    memset(&server, 0, sizeof(sockaddr_in));

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);

    // client和server进行连接
    if (-1 == connect(clientfd, (sockaddr *)&server, sizeof(sockaddr_in))) {
        cerr << "connect server failed" << endl;
        close(clientfd);
        exit(-1);
    }

    // 初始化读写线程通信用的信号量
    sem_init(&rwsem, 0, 0);

    // 连接服务器成功, 启动一个接收消息的子线程
    thread readTask(readTaskHandler, clientfd);
    readTask.detach();

    // 主线程用于接收用户输入, 负责发送数据
    for (;;) {
        // 显示首页面菜单: 登录、注册、退出程序
        cout << "========================" << endl;
        cout << "1. login" << endl;
        cout << "2. register" << endl;
        cout << "3. quit" << endl;
        cout << "========================" << endl;

        int choice = 0;

        // 用户输入验证循环
        while (true) {
            cout << "choice: ";
            cin >> choice;
            // 判断输入是否合法
            if (cin.fail()) {
                // 输入不是整数，清除错误标志
                cin.clear();
                // 清空输入缓冲区
                cin.ignore(10000, '\n');
                cerr << "invalid choice!" << endl;
            } else {
                // 清除残留的换行符
                cin.ignore(10000, '\n');
                break;
            }
        }

        // 根据用户输入执行操作
        switch (choice) {
            // 登录业务
            case 1: {
                char name[50] = {0};
                char password[50] = {0};
                cout << "user name: ";
                cin.getline(name, 50);
                cout << "user password: ";
                cin.getline(password, 50);

                json js;
                js["msgType"] = LOGIN_MSG;
                js["name"] = name;
                js["password"] = password;
                string request = js.dump();

                g_isLoginSuccess = false;

                int len = send(clientfd, request.c_str(), strlen(request.c_str()) + 1, 0);
                if (len == -1) {
                    cerr << "send login msg error: " << request << endl;
                }

                // 等待信号量, 由子线程处理完登录的响应消息后, 通知主线程继续执行
                sem_wait(&rwsem);

                // 用户登录成功
                if (g_isLoginSuccess) {
                    // 进入聊天主菜单
                    isMainMenuRunning = true;
                    mainMenu(clientfd);
                }
                break;
            }
            // 注册业务
            case 2: {
                char name[50] = {0};
                char pwd[50] = {0};
                cout << "user name: ";
                cin.getline(name, 50);
                cout << "user password: ";
                cin.getline(pwd, 50);

                json js;
                js["msgType"] = REGISTER_MSG;
                js["name"] = name;
                js["password"] = pwd;
                string request = js.dump();

                int len = send(clientfd, request.c_str(), strlen(request.c_str()) + 1, 0);
                if (len == -1) {
                    cerr << "send reg msg error: " << request << endl;
                }

                // 等待信号量, 由子线程处理完注册的响应消息后, 通知主线程继续执行
                sem_wait(&rwsem);
                break;
            }
            // 退出程序业务
            case 3:
                close(clientfd);
                sem_destroy(&rwsem);
                exit(0);
            default:
                cerr << "invalid choice!" << endl;
                break;
        }
    }

    return 0;
}

// 处理注册的响应逻辑
void doRegResponse(json &responsejs) {
    // 注册失败
    if (0 != responsejs["errNum"].get<int>()) {
        cerr << "注册失败: " << responsejs["errMsg"].get<string>() << endl;
    }
    // 注册成功
    else {
        cout << "注册成功, 用户 ID: " << responsejs["userId"] << " , 用户名称: " << responsejs["userName"].get<string>()
             << endl;
    }
}

// 处理登录的响应逻辑
void doLoginResponse(json &responsejs) {
    // 登录失败
    if (0 != responsejs["errNum"].get<int>()) {
        cerr << "登录失败: " << responsejs["errMsg"].get<string>() << endl;
        g_isLoginSuccess = false;
    }
    // 登录成功
    else {
        // 记录当前登录用户的基本信息
        g_currentUser.setId(responsejs["userId"].get<int>());
        g_currentUser.setName(responsejs["userName"].get<string>());

        // 记录当前用户的好友列表信息
        if (responsejs.contains("friends")) {
            // 初始化好友列表
            g_currentUserFriendList.clear();

            vector<User> vec = responsejs["friends"];
            for (User &user : vec) {
                g_currentUserFriendList.push_back(user);
            }
        }

        // 记录当前用户的群组列表信息
        if (responsejs.contains("groups")) {
            // 初始化群组列表
            g_currentUserGroupList.clear();

            vector<Group> vec = responsejs["groups"];
            for (Group &group : vec) {
                g_currentUserGroupList.push_back(group);
            }
        }

        // 显示登录用户的基本信息
        showCurrentUserData();

        // 显示当前用户的离线消息（个人聊天信息或者群组消息）
        if (responsejs.contains("offlinemsg")) {
            vector<OfflineMessage> vec = responsejs["offlinemsg"];
            for (OfflineMessage &message : vec) {
                // 离线消息的内容（JSON字符串）
                json content = json::parse(message.getMessage());
                // 离线消息的发送时间
                string datetime = formatTimestampLocal(message.getCreateTime(), "%Y-%m-%d %H:%M:%S");
                // 打印一对一聊天消息
                if (SINGLE_CHAT_MSG == content["msgType"].get<int>()) {
                    cout << "好友消息[" << content["fromId"] << "] " << datetime << " "
                         << content["fromName"].get<string>() << " said: " << content["fromMsg"].get<string>() << endl;
                }
                // 打印群组聊天消息
                else {
                    cout << "群聊消息[" << content["groupId"] << "] " << datetime << " [" << content["fromId"] << "] "
                         << content["fromName"].get<string>() << " said: " << content["groupMsg"].get<string>() << endl;
                }
            }
        }

        g_isLoginSuccess = true;
    }
}

// 子线程（接收消息的线程）执行的业务逻辑
void readTaskHandler(int clientfd) {
    for (;;) {
        char buffer[1024] = {0};
        int len = recv(clientfd, buffer, 1024, 0);  // 阻塞等待消息
        if (-1 == len || 0 == len) {
            close(clientfd);
            exit(-1);
        }

        // 接收ChatServer转发的数据, 反序列化生成JSON数据对象
        json js = json::parse(buffer);

        // 消息类型
        int msgtype = js["msgType"].get<int>();

        // 处理一对一聊天消息
        if (SINGLE_CHAT_MSG == msgtype) {
            string datetime = formatTimestampLocal(js["fromTimestamp"].get<long>(), "%Y-%m-%d %H:%M:%S");
            cout << "好友消息[" << js["fromId"] << "] " << datetime << " " << js["fromName"].get<string>()
                 << " said: " << js["fromMsg"].get<string>() << endl;
            continue;
        }

        // 处理群组聊天消息
        if (GROUP_CHAT_MSG == msgtype) {
            string datetime = formatTimestampLocal(js["fromTimestamp"].get<long>(), "%Y-%m-%d %H:%M:%S");
            cout << "群聊消息[" << js["groupId"] << "] " << datetime << " [" << js["fromId"] << "] "
                 << js["fromName"].get<string>() << " said: " << js["groupMsg"].get<string>() << endl;
            continue;
        }

        // 处理登录响应的业务逻辑
        if (LOGIN_MSG_ACK == msgtype) {
            doLoginResponse(js);
            sem_post(&rwsem);  // 通知主线程, 登录结果处理完成
            continue;
        }

        // 处理注册响应的业务逻辑
        if (REGISTER_MSG_ACK == msgtype) {
            doRegResponse(js);
            sem_post(&rwsem);  // 通知主线程, 注册结果处理完成
            continue;
        }
    }
}

// 显示当前登录成功用户的基本信息
void showCurrentUserData() {
    cout << "======================login user======================" << endl;
    cout << "current login user => id:" << g_currentUser.getId() << " name:" << g_currentUser.getName() << endl;
    cout << "----------------------friend list---------------------" << endl;
    if (!g_currentUserFriendList.empty()) {
        for (User &user : g_currentUserFriendList) {
            cout << user.getId() << " " << user.getName() << " " << user.getState() << endl;
        }
    }
    cout << "----------------------group list----------------------" << endl;
    if (!g_currentUserGroupList.empty()) {
        for (Group &group : g_currentUserGroupList) {
            cout << group.getId() << " " << group.getGroupName() << " " << group.getGroupDesc() << endl;
            for (User &user : group.getUsers()) {
                cout << user.getId() << " " << user.getName() << " " << user.getState() << endl;
            }
        }
    }
    cout << "======================================================" << endl;
}

/////////////////////////////////////////////////////主菜单功能/////////////////////////////////////////////////////

// "help" command handler
void help(int fd = 0, string str = "");
// "singlechat" command handler
void singlechat(int, string);
// "addfriend" command handler
void addfriend(int, string);
// "creategroup" command handler
void creategroup(int, string);
// "joingroup" command handler
void joingroup(int, string);
// "groupchat" command handler
void groupchat(int, string);
// "loginout" command handler
void loginout(int, string);

// 系统支持的客户端命令列表
unordered_map<string, string> commandMap = {{"help", "显示所有支持的命令, 格式 help"},
                                            {"singlechat", "一对一聊天, 格式 singlechat:friendid:message"},
                                            {"addfriend", "添加好友, 格式 addfriend:friendid"},
                                            {"creategroup", "创建群组, 格式 creategroup:groupname:groupdesc"},
                                            {"joingroup", "加入群组, 格式 joingroup:groupid"},
                                            {"groupchat", "群组聊天, 格式 groupchat:groupid:message"},
                                            {"loginout", "退出登录, 格式 loginout"}};

// 注册系统支持的客户端命令处理
unordered_map<string, function<void(int, string)>> commandHandlerMap = {
    {"help", help},           {"singlechat", singlechat}, {"addfriend", addfriend}, {"creategroup", creategroup},
    {"joingroup", joingroup}, {"groupchat", groupchat},   {"loginout", loginout}};

// 主菜单程序
void mainMenu(int clientfd) {
    help();

    char buffer[1024] = {0};
    while (isMainMenuRunning) {
        // 存储用户选择执行的命令
        string command;
        cin.getline(buffer, 1024);
        string commandbuf(buffer);
        int idx = commandbuf.find(":");
        if (-1 == idx) {
            command = commandbuf;
        } else {
            command = commandbuf.substr(0, idx);
        }

        // 查找相应命令的事件处理器
        auto it = commandHandlerMap.find(command);
        if (it == commandHandlerMap.end()) {
            cerr << "invalid input command!" << endl;
            continue;
        }

        // 调用相应命令的事件处理回调函数
        it->second(clientfd, commandbuf.substr(idx + 1, commandbuf.size() - idx));
    }
}

// "help" command handler
void help(int, string) {
    cout << ">>> show command list >>> " << endl;
    for (auto &p : commandMap) {
        cout << p.first << " : " << p.second << endl;
    }
    cout << endl;
}

// "addfriend" command handler
void addfriend(int clientfd, string str) {
    // 数据格式: friendid
    int friendId = atoi(str.c_str());
    if (friendId <= 0) {
        cerr << "add friend command invalid!" << endl;
        return;
    }

    // 请求参数
    json request;
    request["msgType"] = ADD_FRIEND_MSG;
    request["userId"] = g_currentUser.getId();
    request["friendId"] = friendId;

    // 发送数据
    string buffer = request.dump();
    int len = send(clientfd, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);
    if (-1 == len) {
        cerr << "send add friend msg error -> " << buffer << endl;
    }
}

// "singlechat" command handler
void singlechat(int clientfd, string str) {
    // 数据格式: friendid:message
    int idx = str.find(":");
    if (-1 == idx) {
        cerr << "single chat command invalid!" << endl;
        return;
    }

    int friendId = atoi(str.substr(0, idx).c_str());
    string message = str.substr(idx + 1, str.size() - idx);

    // 请求参数
    json request;
    request["msgType"] = SINGLE_CHAT_MSG;
    request["fromId"] = g_currentUser.getId();
    request["fromName"] = g_currentUser.getName();
    request["fromMsg"] = message;
    request["fromTimestamp"] = getTimestampMs();
    request["toId"] = friendId;

    // 发送数据
    string buffer = request.dump();
    int len = send(clientfd, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);
    if (-1 == len) {
        cerr << "send single chat msg error -> " << buffer << endl;
    }
}

// "creategroup" command handler
void creategroup(int clientfd, string str) {
    // 数据格式: groupname:groupdesc
    int idx = str.find(":");
    if (-1 == idx) {
        cerr << "create group command invalid!" << endl;
        return;
    }

    string groupName = str.substr(0, idx);
    string groupDesc = str.substr(idx + 1, str.size() - idx);

    // 请求参数
    json request;
    request["msgType"] = CREATE_GROUP_MSG;
    request["userId"] = g_currentUser.getId();
    request["groupName"] = groupName;
    request["groupDesc"] = groupDesc;

    // 发送数据
    string buffer = request.dump();
    int len = send(clientfd, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);
    if (-1 == len) {
        cerr << "send create group msg error -> " << buffer << endl;
    }
}

// "joingroup" command handler
void joingroup(int clientfd, string str) {
    // 数据格式：groupid
    int groupId = atoi(str.c_str());
    if (groupId <= 0) {
        cerr << "join group command invalid!" << endl;
        return;
    }

    // 请求参数
    json request;
    request["msgType"] = JOIN_GROUP_MSG;
    request["userId"] = g_currentUser.getId();
    request["groupId"] = groupId;

    // 发送数据
    string buffer = request.dump();
    int len = send(clientfd, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);
    if (-1 == len) {
        cerr << "send join group msg error -> " << buffer << endl;
    }
}

// "groupchat" command handler
void groupchat(int clientfd, string str) {
    // 数据格式：groupid:message
    int idx = str.find(":");
    if (-1 == idx) {
        cerr << "group chat command invalid!" << endl;
        return;
    }

    int groupId = atoi(str.substr(0, idx).c_str());
    string groupMsg = str.substr(idx + 1, str.size() - idx);

    // 请求参数
    json request;
    request["msgType"] = GROUP_CHAT_MSG;
    request["fromId"] = g_currentUser.getId();
    request["fromName"] = g_currentUser.getName();
    request["fromTimestamp"] = getTimestampMs();
    request["groupId"] = groupId;
    request["groupMsg"] = groupMsg;

    // 发送数据
    string buffer = request.dump();
    int len = send(clientfd, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);
    if (-1 == len) {
        cerr << "send group chat msg error -> " << buffer << endl;
    }
}

// "loginout" command handler
void loginout(int clientfd, string) {
    // 请求参数
    json request;
    request["msgType"] = LOGIN_OUT_MSG;
    request["userId"] = g_currentUser.getId();

    // 发送数据
    string buffer = request.dump();
    int len = send(clientfd, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);
    if (-1 == len) {
        cerr << "send login out msg error -> " << buffer << endl;
    } else {
        isMainMenuRunning = false;
    }
}