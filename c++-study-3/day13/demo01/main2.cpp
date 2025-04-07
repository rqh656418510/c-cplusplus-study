/**
 * 简单工厂模式和工厂方法模式
 */

#include <iostream>
#include <memory>

// 工厂方法模式的使用

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

// 工厂方法
class CarFactory {

public:
    // 纯虚函数
    virtual unique_ptr<Car> createCar(string name) = 0;

};

// 宝马工厂
class BmwFactory : public CarFactory {

public:
    unique_ptr<Car> createCar(string name) override {
        return unique_ptr<Bmw>(new Bmw(name));
    }

};

// 奥迪工厂
class AudiFactory : public CarFactory {

public:
    unique_ptr<Car> createCar(string name) override {
        return unique_ptr<Audi>(new Audi(name));
    }

};

int main() {
    unique_ptr<CarFactory> bmwFactory(new BmwFactory());
    unique_ptr<Car> car1 = bmwFactory->createCar("X6");
    car1->show();

    unique_ptr<CarFactory> audiFactory(new AudiFactory());
    unique_ptr<Car> car2 = audiFactory->createCar("A8");
    car2->show();

    return 0;
}
