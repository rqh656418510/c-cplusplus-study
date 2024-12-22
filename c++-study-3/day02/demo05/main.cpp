/**
 * 掌握构造函数的初始化列表
 */

#include <iostream>
#include <cstring>

using namespace std;

class CDate {

public:
    // 自定义一个构造函数，编译器不会再自动生成一个默认构造函数（无参构造函数）
    CDate(int year, int month, int day) {
        _year = year;
        _month = month;
        _day = day;
    }

    void show() {
        cout << "year: " << _year << ", month: " << _month << ", day: " << _day << endl;
    }

private:
    int _year;
    int _month;
    int _day;
};

class CGoods {

public:
    // 使用构造函数的初始化列表，可以指定当前对象的成员变量的初始化方式
    CGoods(const char *name, int amount, double price, int year, int month, int day) : _amount(amount), _price(price), _date(year, month, day) {
        strcpy(_name, name);
    }

    void show() {
        cout << "name: " << _name << ", amount: " << _amount << ", price: " << _price << endl;
        _date.show();
    }

private :
    char _name[20];  // 静态分配内存
    int _amount;
    double _price;
    CDate _date;    // 成员对象

};

int main() {
    CGoods goods("Book", 100, 59.9, 2024, 12, 22);
    goods.show();
    return 0;
}
