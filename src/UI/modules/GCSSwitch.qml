import QtQuick

Rectangle {
    id: gcsSwitchRoot
    height: 20
    width: 20
    radius: height / 2
    color: "white"
    border.color: buttonColor
    border.width: 2

    property alias onText:         rightText.text
    property alias offText:        leftText.text
    property alias textColor:      leftText.color
    property alias mouseArea:      mouseArea
    property bool isActive:             false
    Rectangle {
        id: slider
        height: gcsSwitchRoot.height - 8
        width: gcsSwitchRoot.width / 2
        radius: height / 2
        color: conceptColor
        anchors.verticalCenter: parent.verticalCenter
        x: isActive ?  parent.width - width - 4 : 4
        Behavior on x { NumberAnimation { duration: 200 } }
    }
    Text {
        id: leftText
        text: ""
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 10
        color: "#3b3c3d" //textColor
        font.pointSize: fontSize * 0.8
    }
    Text {
        id: rightText
        text: ""
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 10
        color: leftText.color
        font.pointSize: leftText.font.pointSize
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            isActive = !isActive
        }
    }
}
