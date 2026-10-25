import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic

// 主窗口
ApplicationWindow {
    id: root
    width: 1280
    height: 800
    visible: true       // 默认不显示窗口
    title: "Login UI"
    // 外部矩形
    Rectangle {
        width: parent.width
        height: parent.height
        // 背景渐变色
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#4158d0"
            }
            GradientStop {
                position: 1
                color: "#c850c0"
            }
            orientation: Gradient.Horizontal  // 水平渐变
        }
        // 中间矩形
        Rectangle {
            width: 800
            height: 500
            radius: 10 // 圆角效果
            anchors.centerIn: parent  // 居中显示
            // 图片
            Image {
                x: 57
                y: 100
                source: "images/q2.png"
            }
            // 标题
            Text {
                x: 530
                y: 130
                width: 120
                height: 30
                font.pixelSize: 24
                text: qsTr("登录系统")
                color: "#333333"
            }
            // 用户名
            TextField {
                id: username
                x: 440
                y: 200
                width: 300
                height: 50
                font.pixelSize: 20
                leftPadding: 60
                color: "#666666"   // 输入词颜色
                placeholderText: qsTr("用户名或邮箱") // 提示词
                placeholderTextColor: "#999999"  // 提示词颜色
                background: Rectangle {
                    color: "#e6e6e6"
                    border.color: "#e6e6e6"
                    radius: 25
                }
            }
            // 密码
            TextField {
                id: password
                x: username.x
                y: username.y + username.height + 10
                width: username.width
                height: username.height
                font.pixelSize: username.font.pixelSize
                leftPadding: username.leftPadding
                color: username.color   // 输入词颜色
                placeholderText: qsTr("密码")  // 提示词
                placeholderTextColor: username.placeholderTextColor  // 提示词颜色
                echoMode: TextInput.Password
                background: Rectangle {
                    color: username.background.color
                    border.color: username.background.color
                    radius: username.background.radius
                }
            }
            // 登录按钮
            Button {
                x: username.x
                y: password.y + password.height + 10
                width: username.width
                height: username.height
                font.pixelSize: 20
                text: qsTr("登 录")
                onClicked: {
                    print("登录：" + username.text + " : " + password.text);
                }
            }
        }
    }
}
