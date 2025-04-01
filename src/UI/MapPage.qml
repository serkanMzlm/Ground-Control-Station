import QtQuick
import QtLocation
import QtPositioning
import QtQuick.Controls

Item {
    id: mapPage
    height: mainWindow.height // * 0.95
    width: mainWindow.width //* 0.925
    z: -1

    Plugin {
        id: mapPlugin
        name: "osm"
        PluginParameter {
            name: "osm.mapping.custom.host"
            value: "https://www.openstreetmap.org/"
        }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(39.92, 32.8)
        zoomLevel: 10
        onZoomLevelChanged: {
            marker.radius = 1500.0 / Math.pow(2, (map.zoomLevel - 10))
        }

        activeMapType: map.supportedMapTypes[supportedMapTypes.length - 1]

        WheelHandler {
            id: wheel
            acceptedDevices: PointerDevice.Mouse
            rotationScale: 1 / 120
            property: "zoomLevel"
        }

        DragHandler {
            id: drag
            target: null
            onTranslationChanged: delta => map.pan(-delta.x, -delta.y)
        }

        MapCircle {
            id: marker
            center {
                latitude: -27.5
                longitude: 153.0
            }
            radius: 1500.0
            color: 'green'
            border.width: 3
        }
    }

    MouseArea {
        anchors.fill: map
        hoverEnabled: true
        property var coordinate: map.toCoordinate(Qt.point(mouseX, mouseY))
        property var latitude: coordinate.latitude.toFixed(2)
        property var longitude: coordinate.longitude.toFixed(2)

        onClicked: {
            marker.center = map.toCoordinate(Qt.point(mouseX, mouseY))
            marker.visible = true
            console.log("[%1, %2]".arg(latitude).arg(longitude))
        }
        Label {
            x: parent.mouseX - width
            y: parent.mouseY - height - 5
            text: "lat: %1; lon:%2".arg(parent.latitude).arg(parent.longitude)
            color: "black"
        }
    }
}
