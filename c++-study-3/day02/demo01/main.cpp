/**
 * 类和对象、this指针
 */

#include <iostream>
#include <cstring>

using namespace std;

const int NAME_LENGTH = 50;

class CGoods {

public:
    CGoods(const char *name, double price, int amount) {
        strcpy(this->_name, name);
        this->_price = price;
        this->_amount = amount;
    }

    const char *getName() const {
        return this->_name;
    }

    double getPrice() const {
        return this->_price;
    }

    int getAmount() const {
        return this->_amount;
    }

    void setName(char *name) {
        strcpy(this->_name, name);
    }

    void setPrice(double price) {
        this->_price = price;
    }

    void setAmount(int amount) {
        this->_amount = amount;
    }

    void show() {
        cout << "name: " << this->_name << endl;
        cout << "price: " << this->_price << endl;
        cout << "amount: " << this->_amount << endl;
    }

private:
    char _name[NAME_LENGTH]; // 静态分配内存
    double _price;
    int _amount;

};

int main() {
    CGoods good("Book", 80, 3);
    good.show();
    return 0;
}
