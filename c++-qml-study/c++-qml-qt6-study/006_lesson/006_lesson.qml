import QtQuick
import QtQuick.Window

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("QML Study")

    Text {
        x: 280
        y: 200
        font.pixelSize: 25
        text: qsTr("欢迎登录")
    }
}