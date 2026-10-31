import QtQuick
import QtQuick.Window

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("QML Study")

    // 访问同目录的 MyText.qml 文件，直接将文件名（去掉 ".qml" 后缀）作为类型名
    MyText {
        x: 280
        y: 200
    }
}