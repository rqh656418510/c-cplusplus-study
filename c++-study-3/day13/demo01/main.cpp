/**
 * 简单工厂模式和工厂方法模式
 */

#include <iostream>
#include <memory>

// 简单工厂模式的使用

using namespace std;

// 抽象类
class Car {

public:
    Car(string name) : _name(name) {

    }

    // 纯虚函数
    virtual void show() = 0;

protected:
    string _name;

};

// 子类
class Bmw : public Car {

public:

    Bmw(string name) : Car(name) {

    }

    void show() {
        cout << "这是一辆宝马轿车" << endl;
    }

};

// 子类
class Audi : public Car {

public:
    Audi(string name) : Car(name) {

    }

    void show() {
        cout << "这是一辆奥迪轿车" << endl;
    }
};


enum CarType {
    BMW, AUDI
};

// 简单工厂
class SimpleFactory {

public:
    unique_ptr<Car> createCar(CarType type) {
        switch (type) {
            case BMW:
                return unique_ptr<Car>(new Bmw("X5"));
            case AUDI:
                return unique_ptr<Car>(new Audi("A5"));
            default:
                cerr << "传入的工厂参数不正确 : " << type << endl;
                break;
        }
    }
};

int main() {
    unique_ptr<SimpleFactory> factory(new SimpleFactory);

    unique_ptr<Car> car1 = factory->createCar(BMW);
    car1->show();

    unique_ptr<Car> car2 = factory->createCar(AUDI);
    car2->show();

    return 0;
}
