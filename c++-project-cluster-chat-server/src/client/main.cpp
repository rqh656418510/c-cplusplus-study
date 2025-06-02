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

// 用于读写线程之间的通信
sem_t rwsem;
// 控制主菜单页面程序运行
bool isMainMenuRunning = false;
// 记录登录状态
atomic_bool g_isLoginSuccess{false};

// 主聊天页面程序
void mainMenu(int);
// 接收到消息后的处理逻辑
void readTaskHandler(int clientfd);

// 显示当前登录用户的基本信息
void showCurrentUserData();

// 聊天客户端程序实现，主线程用作消息发送线程，子线程用作消息接收线程
int main(int argc, char **argv) {
    if (argc < 3) {
        cerr << "command invalid! example: ./chat_client 127.0.0.1 6000" << endl;
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

    // 连接服务器成功，启动一个接收消息的子线程
    thread readTask(readTaskHandler, clientfd);
    readTask.detach();

    // 主线程用于接收用户输入，负责发送数据
    for (;;) {
        // 显示首页面菜单：登录、注册、退出
        cout << "========================" << endl;
        cout << "1. login" << endl;
        cout << "2. register" << endl;
        cout << "3. quit" << endl;
        cout << "========================" << endl;
        cout << "choice: ";
        int choice = 0;
        cin >> choice;
        cin.get();  // 读掉缓冲区残留的回车键

        switch (choice) {
            // 登录业务
            case 1: {
                int id = 0;
                char pwd[50] = {0};
                cout << "user id: ";
                cin >> id;
                cin.get();  // 读掉缓冲区残留的回车键
                cout << "user password: ";
                cin.getline(pwd, 50);

                json js;
                js["msgType"] = LOGIN_MSG;
                js["id"] = id;
                js["password"] = pwd;
                string request = js.dump();

                g_isLoginSuccess = false;

                int len = send(clientfd, request.c_str(), strlen(request.c_str()) + 1, 0);
                if (len == -1) {
                    cerr << "send login msg error: " << request << endl;
                }

                // 等待信号量，由子线程处理完登录的响应消息后，通知主线程继续执行
                sem_wait(&rwsem);

                // 用户登录成功
                if (g_isLoginSuccess) {
                    // 进入聊天主菜单页面
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

                // 等待信号量，由子线程处理完注册的响应消息后，通知主线程继续执行
                sem_wait(&rwsem);
                break;
            }
            // 退出程序业务
            case 3:
                close(clientfd);
                sem_destroy(&rwsem);
                exit(0);
            default:
                cerr << "invalid input!" << endl;
                break;
        }
    }

    return 0;
}

// 处理注册的响应逻辑
void doRegResponse(json &responsejs) {
    // 注册失败
    if (0 != responsejs["errNum"].get<int>()) {
        cerr << "name is already exist, register error!" << endl;
    }
    // 注册成功
    else {
        cout << "name register success, user id is " << responsejs["userId"] << ", do not forget it!" << endl;
    }
}

// 处理登录的响应逻辑
void doLoginResponse(json &responsejs) {
    // 登录失败
    if (0 != responsejs["errNum"].get<int>()) {
        cerr << responsejs["errMsg"] << endl;
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

        // 显示当前用户的离线消息  个人聊天信息或者群组消息
        if (responsejs.contains("offlinemsg")) {
            vector<OfflineMessage> vec = responsejs["offlinemsg"];
            for (OfflineMessage &message : vec) {
                // 离线消息的内容（JSON）
                json content = json::parse(message.getMessage());
                // 离线消息的发送时间
                string time = formatTimestampLocal(message.getCreateTime(), "%Y-%m-%d %H:%M:%S");
                // 打印一对一聊天消息
                if (SINGLE_CHAT_MSG == content["msgType"].get<int>()) {
                    cout << time << " [" << content["fromId"] << "] " << content["fromName"].get<string>()
                         << " said: " << content["fromMsg"].get<string>() << endl;
                }
                // 打印群组聊天消息
                else {
                    cout << "群聊消息[" << content["groupid"] << "]: " << time << " [" << content["fromId"] << "] "
                         << content["fromName"].get<string>() << " said: " << content["groupmsg"].get<string>() << endl;
                }
            }
        }

        g_isLoginSuccess = true;
    }
}

// 子线程 - 接收线程
void readTaskHandler(int clientfd) {
    for (;;) {
        char buffer[1024] = {0};
        int len = recv(clientfd, buffer, 1024, 0);  // 阻塞等待
        if (-1 == len || 0 == len) {
            close(clientfd);
            exit(-1);
        }

        // 接收ChatServer转发的数据，反序列化生成JSON数据对象
        json js = json::parse(buffer);

        // 消息类型
        int msgtype = js["msgType"].get<int>();

        if (SINGLE_CHAT_MSG == msgtype) {
            cout << time << " [" << js["fromId"] << "] " << js["fromName"].get<string>()
                 << " said: " << js["fromMsg"].get<string>() << endl;
            continue;
        }

        if (GROUP_CHAT_MSG == msgtype) {
            cout << "群聊消息[" << js["groupid"] << "]: " << time << " [" << js["fromId"] << "] "
                 << js["fromName"].get<string>() << " said: " << js["groupmsg"].get<string>() << endl;
        }

        if (LOGIN_MSG_ACK == msgtype) {
            doLoginResponse(js);  // 处理登录响应的业务逻辑
            sem_post(&rwsem);     // 通知主线程，登录结果处理完成
            continue;
        }

        if (REGISTER_MSG_ACK == msgtype) {
            doRegResponse(js);
            sem_post(&rwsem);  // 通知主线程，注册结果处理完成
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

// "help" command handler
void help(int fd = 0, string str = "");
// "chat" command handler
void chat(int, string);
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
unordered_map<string, string> commandMap = {{"help", "显示所有支持的命令，格式 help"},
                                            {"chat", "一对一聊天，格式 chat:friendid:message"},
                                            {"addfriend", "添加好友，格式 addfriend:friendid"},
                                            {"creategroup", "创建群组，格式 creategroup:groupname:groupdesc"},
                                            {"joingroup", "加入群组，格式 joingroup:groupid"},
                                            {"groupchat", "群组聊天，格式 groupchat:groupid:message"},
                                            {"loginout", "退出登录，格式 loginout"}};

// 注册系统支持的客户端命令处理
unordered_map<string, function<void(int, string)>> commandHandlerMap = {
    {"help", help},           {"chat", chat},           {"addfriend", addfriend}, {"creategroup", creategroup},
    {"joingroup", joingroup}, {"groupchat", groupchat}, {"loginout", loginout}};

// 主聊天页面程序
void mainMenu(int clientfd) {
    help();

    char buffer[1024] = {0};
    while (isMainMenuRunning) {
        cin.getline(buffer, 1024);
        string commandbuf(buffer);
        string command;  // 存储命令
        int idx = commandbuf.find(":");
        if (-1 == idx) {
            command = commandbuf;
        } else {
            command = commandbuf.substr(0, idx);
        }
        auto it = commandHandlerMap.find(command);
        if (it == commandHandlerMap.end()) {
            cerr << "invalid input command!" << endl;
            continue;
        }

        // 调用相应命令的事件处理回调，mainMenu对修改封闭，添加新功能不需要修改该函数
        it->second(clientfd, commandbuf.substr(idx + 1, commandbuf.size() - idx));  // 调用命令处理方法
    }
}

// "help" command handler
void help(int, string) {
    cout << "show command list >>> " << endl;
    for (auto &p : commandMap) {
        cout << p.first << " : " << p.second << endl;
    }
    cout << endl;
}

// "addfriend" command handler
void addfriend(int clientfd, string str) {
}

// "chat" command handler
void chat(int clientfd, string str) {
}

// "creategroup" command handler  groupname:groupdesc
void creategroup(int clientfd, string str) {
}

// "joingroup" command handler
void joingroup(int clientfd, string str) {
}

// "groupchat" command handler
void groupchat(int clientfd, string str) {
}

// "loginout" command handler
void loginout(int clientfd, string) {
    json js;
    js["msgType"] = LOGIN_OUT_MSG;
    js["id"] = g_currentUser.getId();
    string buffer = js.dump();

    int len = send(clientfd, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);
    if (-1 == len) {
        cerr << "send loginout msg error -> " << buffer << endl;
    } else {
        isMainMenuRunning = false;
    }
}
