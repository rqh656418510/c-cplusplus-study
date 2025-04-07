/**
 * 简单工厂模式和工厂方法模式
 */

#include <iostream>
#include <memory>

// 简单工厂模式的使用

using namespace std;

// 车
class Car {

public:
    explicit Car(string name) : _name(name) {

    }

    // 纯虚函数
    virtual void show() = 0;

protected:
    string _name;

};

// 宝马车
class Bmw : public Car {

public:
    explicit Bmw(string name) : Car(name) {

    }

    void show() override {
        cout << "这是一辆宝马 " << _name << endl;
    }

};

// 奥迪车
class Audi : public Car {

public:
    explicit Audi(string name) : Car(name) {

    }

    void show() override {
        cout << "这是一辆奥迪 " << _name << endl;
    }
};

// 枚举类型
enum CarType {
    BMW, AUDI
};

// 简单工厂
class SimpleFactory {

public:
    static unique_ptr<Car> createCar(CarType type) {
        switch (type) {
            case BMW:
                return unique_ptr<Car>(new Bmw("X6"));
            case AUDI:
                return unique_ptr<Car>(new Audi("A8"));
            default:
                cerr << "传入的工厂参数不正确 : " << type << endl;
                break;
        }
    }
};

int main() {
    unique_ptr<Car> car1 = SimpleFactory::createCar(BMW);
    car1->show();

    unique_ptr<Car> car2 = SimpleFactory::createCar(AUDI);
    car2->show();

    return 0;
}