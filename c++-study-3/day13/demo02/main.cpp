/**
 * 抽象工厂模式
 */

#include <iostream>
#include <memory>

using namespace std;

// 系列产品一
class Engine {

public:
    explicit Engine(string name) : _name(name) {

    }

    // 纯虚函数，拥有纯虚函数的基类，通常称之为抽象类
    virtual void show() = 0;

protected:
    string _name;

};

class BmwEngine : public Engine {

public:
    BmwEngine(string name) : Engine(name) {

    }

    void show() override {
        cout << "产品名称：" << _name << endl;
    }

};

class AudiEngine : public Engine {

public:
    AudiEngine(string name) : Engine(name) {

    }

    void show() override {
        cout << "产品名称：" << _name << endl;
    }

};

// 系列产品二
class Light {

public:
    explicit Light(string name) : _name(name) {

    }

    // 纯虚函数，拥有纯虚函数的基类，通常称之为抽象类
    virtual void show() = 0;

protected:
    string _name;

};

class BmwLight : public Light {

public:
    BmwLight(string name) : Light(name) {

    }

    void show() override {
        cout << "产品名称：" << _name << endl;
    }

};

class AudiLight : public Light {

public:
    AudiLight(string name) : Light(name) {

    }

    void show() override {
        cout << "产品名称：" << _name << endl;
    }

};

// 抽象工厂（对一组有关联关系的产品簇提供产品对象的统一创建）
class AbstractFactory {

public:
    virtual unique_ptr<Engine> createEngine(string name) = 0;

    virtual unique_ptr<Light> createLight(string name) = 0;

};

// 宝马工厂
class BmwFactory : public AbstractFactory {

public:
    unique_ptr<Engine> createEngine(string name) override {
        return unique_ptr<Engine>(new BmwEngine(name));
    }

    unique_ptr<Light> createLight(string name) override {
        return unique_ptr<Light>(new BmwLight(name));
    }

};

// 奥迪工厂
class AudiFactory : public AbstractFactory {

public:
    unique_ptr<Engine> createEngine(string name) override {
        return unique_ptr<Engine>(new AudiEngine(name));
    }

    unique_ptr<Light> createLight(string name) override {
        return unique_ptr<Light>(new AudiLight(name));
    }
};

int main() {
    unique_ptr<AbstractFactory> bmwFactoy(new BmwFactory());
    unique_ptr<Engine> engine1 = bmwFactoy->createEngine("宝马 X6 引擎");
    unique_ptr<Light> light1 = bmwFactoy->createLight("宝马 X6 大灯");
    engine1->show();
    light1->show();

    unique_ptr<AbstractFactory> audiFactoy(new AudiFactory());
    unique_ptr<Engine> engine2 = audiFactoy->createEngine("奥迪 A8 引擎");
    unique_ptr<Light> light2 = audiFactoy->createLight("奥迪 A8 大灯");
    engine2->show();
    light2->show();

    return 0;
}
