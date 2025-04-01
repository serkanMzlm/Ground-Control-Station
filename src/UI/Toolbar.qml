import QtQuick
import QtQuick.Dialogs

import GCS.SystemDate 1.0

Rectangle {
    id: toolbarRoot
    color: toolbarColor
    width: parent.width
    height: parent.height * 0.05

    SystemDate {
        id: systemDate
    }

    Item {
        id: logoItem
        height: parent.height * 0.7
        width: height
        anchors.left: parent.left
        anchors.leftMargin: height / 2
        anchors.verticalCenter: parent.verticalCenter

        GCSImage {
            source: "/svg/cpu.svg"
            color: titleColor
            anchors.fill: parent
        }
    }

    Text {
        id: dateText
        text: systemDate.date
        font.pointSize: fontSize * 1.2
        color: textColor
        anchors {
            left: logoItem.right
            leftMargin: parent.width * 0.01
            verticalCenter: parent.verticalCenter
        }
    }

    Text {
        id: navigationMenuText
        text: selectPage
        font.bold: true
        font.pointSize: fontSize * 1.5
        color: conceptColor
        anchors {
            centerIn: parent
        }
    }

    Item {
        id: exitItem
        height: parent.height * 0.7
        width: height
        anchors.right: parent.right
        anchors.rightMargin: parent.height * 0.15
        anchors.verticalCenter: parent.verticalCenter

        GCSImage {
            source: "/svg/reject.svg"
            color: titleColor
            anchors.fill: parent
            mouseArea.onClicked: {
                onClicked: Qt.quit()
            }
        }
    }

    Item {
        id: minimizeItem
        height: parent.height * 0.7
        width: height
        anchors.right: exitItem.left
        anchors.rightMargin: parent.height * 0.15
        anchors.verticalCenter: parent.verticalCenter
        Rectangle {
            width: parent.height * 0.8
            height: parent.height * 0.1
            radius: height
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height * 0.15
            color: titleColor
        }
        MouseArea {
            anchors.fill: parent
            onClicked: mainWindow.showMinimized()
        }
    }
}
