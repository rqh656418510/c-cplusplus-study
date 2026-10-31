import QtQuick
import QtQuick.Controls

Item {
    width: 640
    height: 480
    Text {
        id: helloText
        text: "Hello World"
        font.pixelSize: 32
        anchors.centerIn: parent
    }
}