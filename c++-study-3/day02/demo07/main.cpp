/**
 * 掌握类的各种成员方法以及区别
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

    void show() const {
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
        _count++;
    }

    void show() {
        cout << "name: " << _name << ", amount: " << _amount << ", price: " << _price << endl;
        _date.show();
    }

    void show() const {
        cout << "name: " << _name << ", amount: " << _amount << ", price: " << _price << endl;
        _date.show();
    }

    // 静态成员函数
    static void showGoodsCount() {
        cout << "count: " << _count << endl;
    }

private :
    char _name[20];  // 静态分配内存
    int _amount;
    double _price;
    CDate _date;    // 成员对象
    static int _count;  // 静态成员变量

};

// 静态成员变量必须在类外进行定义并初始化
int CGoods::_count = 0;

int main() {
    CGoods goods1("Book", 100, 59.9, 1949, 12, 22);
    goods1.show();

    CGoods goods2("ball", 105, 68, 1949, 12, 22);
    goods2.show();

    CGoods::showGoodsCount();

    const CGoods goods3("car", 105, 68, 1949, 12, 22);
    goods3.show();

    return 0;
}
