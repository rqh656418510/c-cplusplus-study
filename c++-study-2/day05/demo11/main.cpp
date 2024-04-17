/**
 * 继承的引出
 */
#include <iostream>

using namespace std;

// 基类（父类）
class WebSite {

public:
    void header() {
        cout << "Header" << endl;
    }

    void footer() {
        cout << "Footer" << endl;
    }

    void left() {
        cout << "Left" << endl;
    }

    void content() {
        cout << "Content" << endl;
    }
};

// 派生类（子类）
class NewsWebSite : public WebSite {

public:

    void content() {
        cout << "News Content" << endl;
    }

};

// 派生类（子类）
class CarWebSite : public WebSite {

public:

    void content() {
        cout << "Car Content" << endl;
    }

};

void test01() {
    NewsWebSite news;
    news.header();
    news.left();
    news.content();
    news.footer();

    CarWebSite car;
    car.header();
    car.left();
    car.content();
    car.footer();
}

int main() {
    test01();
    return 0;
}
