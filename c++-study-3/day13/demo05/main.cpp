/**
 * 代理模式
 */

#include <iostream>
#include <memory>

using namespace std;

// 抽象类（接口）
class VideoApp {

public:
    // 纯虚函数，拥有纯虚函数的基类，通常称之为抽象类
    virtual void freeMovie() = 0;

    virtual void vipMovie() = 0;

    virtual void ticketMovie() = 0;

    // 虚析构函数
    virtual ~VideoApp() {};

};

// 真实类
class QuickVideoApp : public VideoApp {

public:
    void freeMovie() override {
        cout << "观看免费电影" << endl;
    }

    void vipMovie() override {
        cout << "观看 VIP 电影" << endl;
    }

    void ticketMovie() override {
        cout << "用券观看电影" << endl;
    }

};

// 代理类（包含权限验证逻辑）
class FreeVideoAppProxy : public VideoApp {

public:
    FreeVideoAppProxy() {
        _app = new QuickVideoApp();
    }

    ~FreeVideoAppProxy() {
        delete _app;
    }

    void freeMovie() override {
        _app->freeMovie();
    }

    void vipMovie() override {
        cout << "您目前只是普通用户，需要升级成为 VIP 用户，才能观看电影" << endl;
    }

    void ticketMovie() override {
        cout << "您的账户没有电影券，需要购买电影券，才能观看电影" << endl;
    }

private:
    VideoApp *_app;

};

// 代理类（包含权限验证逻辑）
class VipVideoAppProxy : public VideoApp {

public:
    VipVideoAppProxy() {
        _app = new QuickVideoApp();
    }

    ~VipVideoAppProxy() {
        delete _app;
    }

    void freeMovie() override {
        _app->freeMovie();
    }

    void vipMovie() override {
        _app->vipMovie();
    }

    void ticketMovie() override {
        cout << "您的账户没有电影券，需要购买电影券，才能观看电影" << endl;
    }

private:
    VideoApp *_app;

};

void watchMovie(unique_ptr<VideoApp> &app) {
    app->freeMovie();
    app->vipMovie();
    app->ticketMovie();
}

int main() {
    unique_ptr<VideoApp> freeApp(new FreeVideoAppProxy());
    watchMovie(freeApp);

    cout << "--------------------------------------------------------" << endl;

    unique_ptr<VideoApp> vipApp(new VipVideoAppProxy());
    watchMovie(vipApp);

    return 0;
}