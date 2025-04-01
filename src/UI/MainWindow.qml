import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Window

import QtLocation
import QtPositioning
import QtQuick.Controls
import QtLocation

import GCS.ROSManager 1.0

ApplicationWindow {
    id: mainWindow

    visibility: Window.FullScreen
    width: mainWindow.screen.width * 0.5
    height: mainWindow.screen.height * 0.5

    minimumWidth: mainWindow.screen.width * 0.5
    minimumHeight: mainWindow.screen.height * 0.5

    visible: true
    color: backgroundColor
    title: qsTr("Command Center Unit")

    property bool isDarkTheme: true
    property color lineColor: "#929292"
    property color iconColor: isDarkTheme ? "#3b3c3d" : "#F5F5F5"
    property color textColor: isDarkTheme ? "#e0e0e0" : "#3b3c3d"
    property color titleColor: isDarkTheme ? "#FFFFFF" : "#1d1c1c"
    property color buttonColor: isDarkTheme ? "#444648" : "#cccbc8"
    property color toolbarColor: isDarkTheme ? "#2c2e30" : "#cccbc8"
    property color conceptColor: isDarkTheme ? "#FF6600" : "#006fff"
    property color backgroundColor: isDarkTheme ? "#1D1F21" : "#fffefb"

    property bool isMaximized: false
    property bool mapVisible: false
    property bool isAutoDecet: true
    property string selectPage: "Home"
    property int fontSize: (height <= 0.01 ? 0.01 : height * 0.015)

    Toolbar {
        id: toolbar
    }

    ROSManager {
        id: _ros2
    }

    MenuPanel {
        id: menuPanel
        width: parent.width * 0.07
        height: parent.height * 0.95

        anchors.top: toolbar.bottom
        anchors.left: parent.left

        Loader {
            id: pageLoader
            anchors.bottom: parent.bottom
            anchors.left: parent.right
            source: "TestPage.qml"
            z: -1
        }
    }

    MapPage {
        id: mapPage
        height: mainWindow.height // * 0.95
        width: mainWindow.width //* 0.925
        z: -1
        visible: mapVisible
    }
}
