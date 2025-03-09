import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: settingsPage
    height: mainWindow.height * 0.95
    width: mainWindow.width * 0.925

    property bool value: false
    property var iconScale: 0.25

    GCSImage {
        id: reverseImage
        width: parent.height * 0.1
        height: width
        anchors.centerIn: parent
        source: "/images/joystick/reverse_blue.png"
        overlayEnabled: false
        mouseArea.onPressed: {
            reverseImage.scale = 1.3
            reverseImage.source = settingsPage.value ? "/images/joystick/reverse_blue.png" : "/images/joystick/reverse_red.png"
            settingsPage.value = !settingsPage.value
        }
        mouseArea.onReleased: reverseImage.scale = 1.0
    }

    Rectangle {
        id: emptyRec
        height: parent.height * 0.15
        width: height * 6
        radius: height * 0.1
        color: "#D9D9D9"
        anchors.bottom: reverseImage.top
        anchors.horizontalCenter: settingsPage.horizontalCenter
        anchors.bottomMargin: height
        clip: true
        Rectangle {
            id: ball
            x: emptyRec.width / 2 - ball.width * 0.5
            y: emptyRec.height / 2 - ball.height * 0.5
            width: parent.height * 0.3
            height: width
            radius: width * 0.5
            color: "#59BDB7"
        }
        MouseArea {
            anchors.fill: parent
            onPositionChanged: {
                if (mouseX > 0 && mouseX < emptyRec.width) {
                    ball.x = mouseX - ball.width * 0.5
                }
                if (mouseY > 0 && mouseY < emptyRec.height) {
                    ball.y = mouseY - ball.height * 0.5
                }
                _ros2.pointStateChanged(ball.x, ball.y)
            }
        }
    }

    Item {
        id: leftRec
        height: settingsPage.height * 0.25
        width: height
        anchors.verticalCenter: parent.verticalCenter
        x: settingsPage.value ? settingsPage.width * 0.5 - width
                                * 2 : settingsPage.width * 0.5 + width
        GCSImage {
            id: upImage
            width: parent.height * settingsPage.iconScale
            height: width
            source: "/images/joystick/up.png"
            overlayEnabled: false
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            mouseArea.onPressed: {
                upImage.opacity = 0.5
                _ros2.buttonChanged(0)
            }
            mouseArea.onReleased: upImage.opacity = 1.0
        }
        GCSImage {
            id: downImage
            width: upImage.width
            height: width
            source: "/images/joystick/down.png"
            overlayEnabled: false
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            mouseArea.onPressed: {
                downImage.opacity = 0.5
                _ros2.buttonChanged(1)
            }
            mouseArea.onReleased: downImage.opacity = 1.0
        }
        GCSImage {
            id: leftImage
            width: upImage.width
            height: width
            source: "/images/joystick/left.png"
            overlayEnabled: false
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            mouseArea.onPressed: {
                leftImage.opacity = 0.5
                _ros2.buttonChanged(2)
            }
            mouseArea.onReleased: leftImage.opacity = 1.0
        }
        GCSImage {
            id: rightImage
            width: upImage.width
            height: width
            source: "/images/joystick/right.png"
            overlayEnabled: false
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            mouseArea.onPressed: {
                rightImage.opacity = 0.5
                _ros2.buttonChanged(3)
            }
            mouseArea.onReleased: rightImage.opacity = 1.0
        }
    }

    Item {
        id: rightRec
        height: leftRec.height
        width: height
        anchors.verticalCenter: parent.verticalCenter
        x: settingsPage.value ? settingsPage.width * 0.5
                                + width : settingsPage.width * 0.5 - width * 2
        GCSImage {
            id: triangleImage
            width: parent.height * settingsPage.iconScale
            height: width
            source: "/images/joystick/triangle.png"
            overlayEnabled: false
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            mouseArea.onPressed: {
                triangleImage.scale = 1.3
                _ros2.buttonChanged(4)
            }
            mouseArea.onReleased: triangleImage.scale = 1.0
        }
        GCSImage {
            id: xImage
            width: triangleImage.width
            height: width
            source: "/images/joystick/x.png"
            overlayEnabled: false
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            mouseArea.onPressed: {
                xImage.scale = 1.3
                _ros2.buttonChanged(5)
            }
            mouseArea.onReleased: xImage.scale = 1.0
        }
        GCSImage {
            id: recImage
            width: triangleImage.width
            height: width
            source: "/images/joystick/rectangle.png"
            overlayEnabled: false
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            mouseArea.onPressed: {
                recImage.scale = 1.3
                _ros2.buttonChanged(6)
            }
            mouseArea.onReleased: recImage.scale = 1.0
        }
        GCSImage {
            id: circleImage
            width: triangleImage.width
            height: width
            source: "/images/joystick/circle.png"
            overlayEnabled: false
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            mouseArea.onPressed: {
                circleImage.scale = 1.3
                _ros2.buttonChanged(7)
            }
            mouseArea.onReleased: circleImage.scale = 1.0
        }
    }
}
