import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic

// 主窗口
ApplicationWindow {
    id: root
    width: 1280
    height: 800
    visible: true       // 默认显示窗口
    title: "Login UI"
    color: "#00000000"
    flags: Qt.FramelessWindowHint  // 隐藏窗口的标题栏
    property int dragX: 0
    property int dragY: 0
    property bool dragging: false // 是否正在拖动（自定义窗口拖动状态属性）
    // 主窗口背景矩形
    Rectangle {
        width: parent.width
        height: parent.height
        radius: 10
        // 鼠标区域，用于拖动无边框窗口
        MouseArea {
            width: parent.width
            height: 100
            onPressed: {
                root.dragX = mouseX;
                root.dragY = mouseY;
                root.dragging = true;
            }
            onReleased: {
                root.dragging = false;
            }
            onPositionChanged: {
                if (root.dragging) {
                    root.x += mouseX - root.dragX;
                    root.y += mouseY - root.dragY;
                    root.dragX = mouseX;
                    root.dragY = mouseY;
                }
            }
        }
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
            orientation: Gradient.Horizontal  // 设置背景水平渐变色
        }
        // 登录面板矩形
        Rectangle {
            width: 800
            height: 500
            radius: 10 // 圆角效果
            anchors.centerIn: parent  // 居中显示
            // 图片
            Image {
                id: image
                x: 57
                y: 100
                source: "images/q2.png"
                // 定义图片旋转状态，并通过 Transition 实现状态切换动画
                states: [
                    State {
                        name: "rotated"
                        PropertyChanges {
                            target: image
                            rotation: 180
                        }
                    }
                ]
                transitions: Transition {
                    RotationAnimation {
                        duration: 1000   // 动画持续时间（毫秒）
                        direction: RotationAnimation.Counterclockwise
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (image.state == "rotated") {
                            image.state = "";
                        } else {
                            image.state = "rotated";
                        }
                    }
                }
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
                color: "#666666"   // 输入文本颜色
                placeholderText: qsTr("用户名或邮箱") // 占位提示文本
                placeholderTextColor: "#999999"  // 占位提示文本颜色
                background: Rectangle {
                    color: "#e6e6e6"
                    border.color: "#e6e6e6"
                    radius: 25
                }
                // 图标
                Image {
                    x: 30
                    y: 15
                    width: 20
                    height: 20
                    source: username.activeFocus ? "images/u2.png" : "images/u1.png"
                }
                // 输入框入场动画，使其沿 Y 轴移动
                NumberAnimation on y {
                    from: username.y - 50
                    to: username.y
                    duration: 300  // 动画持续时间（毫秒）
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
                color: username.color   // 输入文本颜色
                placeholderText: qsTr("密码")  // 占位提示文本
                placeholderTextColor: username.placeholderTextColor  // 占位提示文本颜色
                echoMode: TextInput.Password
                background: Rectangle {
                    color: username.background.color
                    border.color: username.background.color
                    radius: username.background.radius
                }
                // 图标
                Image {
                    x: 30
                    y: 15
                    width: 20
                    height: 20
                    source: password.activeFocus ? "images/p2.png" : "images/p1.png"
                }
            }
            // 登录按钮
            Button {
                id: submit
                x: username.x
                y: password.y + password.height + 10
                width: username.width
                height: username.height
                font.pixelSize: 20
                text: qsTr("登 录")
                background: Rectangle {
                    radius: 25
                    color: {
                        if (submit.down) {
                            return "#00b846";
                        }
                        if (submit.hovered) {
                            return "#333333";
                        }
                        return "#57b846";
                    }
                }
                // 处理登录按钮点击事件
                onClicked: {
                    print("登录，" + username.text + " : " + password.text);
                }
            }
        }
    }
    // 关闭窗口的按钮
    Rectangle {
        x: root.width - 35
        y: 5
        width: 30
        height: 30
        color: "#00000000"
        Text {
            text: "×"
            font.pixelSize: 28
            anchors.centerIn: parent
        }
        // 鼠标区域，用于处理关闭按钮的交互
        MouseArea {
            anchors.fill: parent
            onEntered: parent.color = "#1BFFFFFF"
            onExited: parent.color = "#00000000"
            onPressed: parent.color = "#3BFFFFFF"
            onReleased: parent.color = "#1BFFFFFF"
            // 点击事件
            onClicked: {
                root.close();
            }
        }
    }
}
