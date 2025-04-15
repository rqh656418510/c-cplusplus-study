/**
 * 适配器模式
 */

#include <iostream>

using namespace std;

// VGA 接口
class VGA {

public:
    // 纯虚函数，拥有纯虚函数的基类，通常称之为抽象类
    virtual void play() = 0;

    // 虚析构函数
    ~VGA() {}

};

// 支持 VGA 接口的投影仪
class Device01 : public VGA {

public:
    void play() override {
        cout << "使用 VGA 接口的投影仪播放视频" << endl;
    }

};

// 电脑类（只支持 VGA 接口）
class Computer {

public:
    // 由于电脑只支持 VGA 接口，所以该函数的参数也只能支持 VGA 接口的指针/引用
    void playVideo(VGA *vga) {
        vga->play();
    }

};

// HDMI 接口
class HDMI {

public:
    // 纯虚函数，拥有纯虚函数的基类，通常称之为抽象类
    virtual void play() = 0;

    // 虚析构函数
    ~HDMI() {}

};

// 支持 HDMI 接口的投影仪
class Device02 : public HDMI {

public:
    void play() override {
        cout << "使用 HDMI 接口的投影仪播放视频" << endl;
    }

};

// 由于电脑（VGA接口）和投影仪（HDMI接口）无法直接相连，所以需要添加适配器类
class VGAToHDMIAdapter : public VGA {

public:
    VGAToHDMIAdapter(HDMI *p) : pHdmi(p) {

    }

    // 此方法相当于转换器，将 HDMI 信号转换为 VGA 信号
    void play() override {
        pHdmi->play();
    }

private :
    HDMI *pHdmi;
};

int main() {
    Computer computer;

    Device01 dev1;
    computer.playVideo(&dev1);

    Device02 dev2;
    VGAToHDMIAdapter adapter(&dev2);
    computer.playVideo(&adapter);

    return 0;
}