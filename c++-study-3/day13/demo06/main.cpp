/**
 * 观察者模式
 */

#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

// 观察者接口
class Observer {

public:
    // 接收通知
    virtual void update(int state) = 0;

    // 虚析构函数
    virtual ~Observer() {}

};

// 具体的观察者
class ConcreteObserverA : public Observer {

public:
    // 接收通知
    void update(int state) override {
        cout << "ConcreteObserverA receive message, state is " << state << endl;
    }

};

// 具体的观察者
class ConcreteObserverB : public Observer {

public:
    // 接收通知
    void update(int state) override {
        cout << "ConcreteObserverB receive message, state is " << state << endl;
    }

};

// 具体的观察者
class ConcreteObserverC : public Observer {

public:
    // 接收通知
    void update(int state) override {
        cout << "ConcreteObserverC receive message, state is " << state << endl;
    }

};

// 主题接口（被观察者）
class Subject {
public:
    // 注册观察者
    virtual void attach(int state, Observer *observer) = 0;

    // 移除观察者
    virtual void detach(int state, Observer *observer) = 0;

    // 通知观察者
    virtual void notify(int state) = 0;

    // 虚析构函数
    virtual ~Subject() {}
};


// 具体的主题（被观察者）
class ConcreteSubject : public Subject {

public:
    // 注册观察者
    void attach(int state, Observer *observer) {
        auto it = _subMap.find(state);
        if (it != _subMap.end()) {
            it->second.push_back(observer);
        } else {
            list<Observer *> list;
            list.push_back(observer);
            _subMap.insert(make_pair(state, list));
        }
    }

    // 移除观察者
    void detach(int state, Observer *observer) {
        auto it = _subMap.find(state);
        if (it != _subMap.end()) {
            list<Observer *> &list = it->second;
            for (auto it = list.begin(); it != list.end();) {
                if (*it == observer) {
                    it = list.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }

    // 通知观察者
    void notify(int state) {
        auto it = _subMap.find(state);
        if (it != _subMap.end()) {
            for (Observer *pObserver : it->second) {
                pObserver->update(state);
            }
        }
    }

private:
    // 观察者的集合
    unordered_map<int, list<Observer *>> _subMap;

};

int main() {
    // 主题（被观察者）
    ConcreteSubject subject;

    // 观察者
    ConcreteObserverA obsA;
    ConcreteObserverB obsB;
    ConcreteObserverC obsC;

    // 注册观察者
    subject.attach(1, &obsA);
    subject.attach(1, &obsB);
    subject.attach(2, &obsA);
    subject.attach(2, &obsC);

    // 移除观察者
    subject.detach(2, &obsA);

    // 通知观察者
    subject.notify(1);
    subject.notify(2);

    return 0;
}