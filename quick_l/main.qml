import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    visible: true
    width: 400
    height: 300
    title: "Image Fade Example"

    Image {
        id: image
        source: "罗捷1.jpeg"
        width: 200
        height: 200
        anchors.centerIn: parent
        opacity: 0  // 初始化透明度为 0

//        NumberAnimation {
//            id: fadeAnimation
//            target: image
//            property: "opacity"
//            from: 0  // 从完全透明开始
//            to: 1    // 淡入到完全不透明
//            duration: 3000  // 动画持续时间为 1 秒

                NumberAnimation {
                    id: fadeAnimation
                    target: image
                    property: "opacity"
                    from: 1.0
                    to: 0.0
                    duration: 1000 // 持续时间，可以根据需要调整
                }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (fadeAnimation.running) {
                    // 如果动画正在运行，则停止它
                    fadeAnimation.stop()
                }
                // 否则，重新启动动画
                fadeAnimation.start()
            }
        }
    }
}
