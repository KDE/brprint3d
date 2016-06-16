import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Rectangle{
    id: bedSet
    color: "#31363b"
    width: parent.width
    property bool heatedBed: true

        GridLayout{
        columns: 3
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5
        enabled: heatedBed ? true : false

        Text{
            text: qsTr("Area X:")
            color: "#eff0f1"
        }
        MTextInput{

        }
        Text {
            text: qsTr("mm")
            color: "#eff0f1"
        }

        Text{
            text: qsTr("Area Y:")
            color: "#eff0f1"
        }
        MTextInput{

        }
        Text {
            text: qsTr("mm")
            color: "#eff0f1"
        }

        Text{
            text: qsTr("Area Z:")
            color: "#eff0f1"
        }
        MTextInput{

        }
        Text {
            text: qsTr("mm")
            color: "#eff0f1"
        }

        Text{
            text: qsTr("Temperature:")
            color: "#eff0f1"
        }
        MTextInput{

        }
        Text {
            text: qsTr("ºC")
            color: "#eff0f1"
        }
    }
}

