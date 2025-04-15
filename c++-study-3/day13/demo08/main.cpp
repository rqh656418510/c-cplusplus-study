/**
 * 装饰器模式
 */

#include <iostream>

using namespace std;

// 抽象组件
class Coffee {

public:
    virtual string getDescription() = 0;

    virtual double cost() = 0;

    virtual ~Coffee() {}

};

// 具体组件
class BasicCoffee : public Coffee {

public:
    string getDescription() override {
        return "Basic Coffee";
    }

    double cost() override {
        return 5.0;
    }

};

// 抽象装饰器
class CoffeeDecorator : public Coffee {

protected:
    Coffee *decoratedCoffee;

public:
    CoffeeDecorator(Coffee *coffee) : decoratedCoffee(coffee) {}

};

// 具体装饰器
class Milk : public CoffeeDecorator {

public:
    Milk(Coffee *coffee) : CoffeeDecorator(coffee) {}

    string getDescription() override {
        return decoratedCoffee->getDescription() + " + Milk";
    }

    double cost() override {
        return decoratedCoffee->cost() + 1.0;
    }

};

int main() {
    Coffee *basicCoffee = new BasicCoffee();
    Coffee *milkCoffee = new Milk(basicCoffee);
    cout << milkCoffee->getDescription() << endl;
    cout << milkCoffee->cost() << endl;

    delete milkCoffee;
    delete basicCoffee;
}