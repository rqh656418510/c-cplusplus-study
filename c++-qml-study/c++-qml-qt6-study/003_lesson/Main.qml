import QtQuick
import QtQuick.Window

// 主窗口
Window {
    width: 640
    height: 480
    visible: true
    title: "Hello World"
    HelloPage {
        anchors.fill: parent
    }
}