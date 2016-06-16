import QtQuick 2.5
import QtQuick 2.0
import QtQuick.Window 2.2

Rectangle{
    id: root
    property color buttonColor: "transparent"
    property color onHoverColor: "mediumslateblue"
    property color onClickedColor: "red"
    property  alias text: label.text
    property alias source: icon.source
    signal clicked

    anchors.left: parent.left
    anchors.right: parent.right

    height: Screen.height /8

    Image {
        id: icon
        width: parent.width /2
        height: parent.height /1.5
        anchors.centerIn: parent
    }

    Text {
        id: label
        horizontalAlignment: parent.Center
        anchors.bottom: parent.bottom
        color: "white"
    }

    MouseArea{
        id: mArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            root.clicked()
        }
    }

    color: mArea.containsMouse ? onHoverColor :buttonColor
}
