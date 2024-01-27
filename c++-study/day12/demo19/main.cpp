/*
 * 1. STL 综合案例 - 学校演讲比赛
*/

#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <numeric>
#include <functional>
#include <ctime>

using namespace std;

// 选手
class Speaker {

public:

    int code;       // 编号
    string name;    // 姓名
    int score[3];   // 分数

};

/**
 * 创建选手
 * @param v 选手编号
 * @param m 关联选手编号与具体的选手
 */
void createSpeaker(vector<int> &v, map<int, Speaker> &m) {
    string nameSeed = "ABCDEFGHIJKLMNOPQRSTUVWX";
    for (int i = 0; i < nameSeed.size(); i++) {
        int code = i + 100;
        string name = "选手";
        name += nameSeed[i];

        Speaker speaker;
        speaker.code = code;
        speaker.name = name;
        for (int j = 0; j < 3; j++) {
            speaker.score[j] = 0;
        }

        v.push_back(code);
        m.insert(make_pair(code, speaker));
    }
}

/**
 * 抽签
 * @param v 选手编号
 */
void speechDraw(vector<int> &v) {
    random_shuffle(v.begin(), v.end());
}

/**
 * 比赛
 * @param index 第几轮比赛
 * @param v1 选手编号
 * @param m 关联选手编号与具体的选手
 * @param v2 进入下一轮比赛的选手编号
 */
void speechContest(int index, vector<int> &v1, map<int, Speaker> &m, vector<int> &v2) {

    int num = 0;
    multimap<int, int, greater<int>> groupMap; // key: 选手的分数，value: 选手的编号

    for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
        num++;
        // 打分
        deque<int> d;
        for (int i = 0; i < 10; i++) {
            int score = rand() % 40 + 60;
            d.push_back(score);
        }
        // 排序
        sort(d.begin(), d.end());
        // 去除最高最低分数
        d.pop_back();
        d.pop_front();
        // 累积分数
        int sum = accumulate(d.begin(), d.end(), 0);
        // 平均分数
        int avg = sum / d.size();
        // 将平均分放进map容器中
        m[*it].score[index - 1] = avg;

        // 每6个人一组，取前三名晋级
        groupMap.insert(make_pair(avg, *it));
        if (num % 6 == 0) {
            // 取前三名晋级下一轮比赛
            int count = 0;
            for (multimap<int, int, greater<int>>::iterator mit = groupMap.begin(); mit != groupMap.end() && count < 3; mit++, count++) {
                v2.push_back(mit->second);
            }
            groupMap.clear();
        }
    }
}

/**
 * 显示比赛结果
 * @param index 第几轮比赛
 * @param v 进入下一轮比赛的选手编号
 * @param m 关联选手编号与具体的选手
 */
void showScore(int index, vector<int> &v, map<int, Speaker> &m) {
    cout << endl << "第 " << index << " 轮比赛成绩如下：" << endl;
    for (map<int, Speaker>::iterator it = m.begin(); it != m.end(); it++) {
        if (it->second.score[index - 1] != 0) {
            cout << "选手编号: " << it->first << " 选手名称: " << it->second.name << " 选手得分: " << it->second.score[index - 1] << endl;
        }
    }

    cout << "第 " << index << " 轮晋级的选手如下：" << endl;
    for (vector<int>::iterator vit = v.begin(); vit != v.end(); vit++) {
        cout << *vit << " ";
    }

    cout << endl;
}

int main() {

    srand((unsigned int) time(NULL));

    vector<int> v1;     // 选手编号
    map<int, Speaker> m;    // 关联选手编号与具体的选手

    createSpeaker(v1, m);  // 创建选手

    speechDraw(v1);     // 第一轮比赛抽签
    vector<int> v2; // 进入下一轮比赛的选手编号
    speechContest(1, v1, m, v2);  // 第一轮比赛
    showScore(1, v2, m);   // 显示第一轮比赛结果

    speechDraw(v2); // 第二轮比赛抽签
    vector<int> v3; // 进入下一轮比赛的选手编号
    speechContest(2, v2, m, v3); // 第二轮比赛
    showScore(2, v3, m); // 显示第二轮比赛结果

    speechDraw(v3); // 第三轮比赛抽签
    vector<int> v4; // 进入下一轮比赛的选手编号
    speechContest(3, v3, m, v4); // 第三轮比赛
    showScore(3, v4, m); // 显示第三轮比赛结果

    return 0;
}
