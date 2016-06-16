import QtQuick 2.5
import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Rectangle{
    id: root
    property color buttonColor: "transparent"
    property color onHoverColor: "#31363b"
    property color onClickedColor: "#3daee9"//"#1cdc9a" Green
    property alias text: label.text
    property alias source: icon.source
    property bool clickControl: false
    signal clicked

    anchors.left: parent.left
    anchors.right: parent.right

    height: Screen.height /8
    ColumnLayout{
        anchors.fill: parent
        Image {
            id: icon
            width: parent.width /2
            height: parent.height /1.5
        }

        Text {
            id: label
            Layout.alignment: Qt.AlignCenter
            color: "white"
            text: qsTr("a")
        }
    }

    MouseArea{
        id: mArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            root.clicked()
        }
    }

    color: mArea.containsMouse ? onHoverColor : clickControl ? onClickedColor : buttonColor
}
