import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

Item {
    id: menuPanelRoot

    property int selected_index: 0

    property var navItems: [{
            "label": "Home",
            "iconSource": "/svg/home.svg",
            "page": "TestPage.qml"
        }, {
            "label": "Joystick",
            "iconSource": "/svg/console.svg",
            "page": "JoystickPage.qml"
        }, {
            "label": "Camera",
            "iconSource": "/svg/camera.svg",
            "page": "TestPage.qml"
        }, {
            "label": "Map",
            "iconSource": "/svg/map.svg",
            "page": "MapPage.qml"
        }, {
            "label": "Settings",
            "iconSource": "/svg/setting.svg",
            "page": "SettingsPage.qml"
        }]

    Rectangle {
        width: 2
        height: parent.height * 0.8
        color: lineColor
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
    }

    ColumnLayout {
        height: parent.height * 0.4
        width: parent.width * 0.6
        anchors.centerIn: parent
        spacing: width * 0.1
        Repeater {
            model: navItems
            Rectangle {
                Layout.fillHeight: true
                width: height
                radius: height * 0.2
                color: menuPanelRoot.selected_index === index ? conceptColor : buttonColor
                GCSImage {
                    source: modelData.iconSource !== "" ? modelData.iconSource : "/svg/more.svg"
                    color: titleColor
                    anchors.margins: parent.width * 0.12
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectCrop
                    mouseArea.onClicked: {
                        menuPanelRoot.selected_index = index
                        selectPage = modelData.label
                        pageLoader.source = menuPanelRoot.selected_index == 3 ? "" : modelData.page
                        if (menuPanelRoot.selected_index == 3) {
                            mainWindow.mapVisible = true
                        } else {
                            mainWindow.mapVisible = false
                        }
                    }
                }
            }
        }
    }
}
