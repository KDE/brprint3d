import QtQuick 2.5
import QtQuick 2.0
import QtQuick.Window 2.2

Rectangle{
    id: root
    property color buttonColor: "midnightblue"
    property color onHoverColor: "mediumslateblue"
    property  alias text: label.text
    signal clicked

    width: Screen.width /10
    height: Screen.height /8

    Text {
        id: label
        horizontalAlignment: parent.Center
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
