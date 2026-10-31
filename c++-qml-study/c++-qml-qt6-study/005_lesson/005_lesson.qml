import QtQuick
import QtQuick.Window

// 导入 QtQuick.Controls 模块，并为其设置别名 "Cont" 以区分或简化调用
import QtQuick.Controls as Cont

// 导入本地目录 "./MyLib" 中的 QML 组件
import "./MyLib"

// 导入本地 JS 文件，并使用带别名的写法
import "./myjs.js" as MyJs

Window {
    width: 640
    height: 480
    visible: true
    title: MyJs.getTitle()   // 通过别名调用 JS 代码

    // 通过别名 Cont 访问 Controls 模块中的 Button 组件
    Cont.Button {
        x: 280
        y: 200
        width: 80
        height: 40
        text: MyJs.getSubmitText()   // 通过别名调用 JS 代码
        onClicked: {
            MyJs.onBtnClick();   // 通过别名调用 JS 代码
        }
    }

    // 本地目录下的 QML 文件在导入后，直接使用其大写开头的文件名（去掉 .qml 后缀）作为组件类型
    MyText {
        x: 270
        y: 100
     }
}