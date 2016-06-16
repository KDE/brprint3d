import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Rectangle{

    id: bedSet
    color: "black"
    width: parent.width
        GridLayout{
        columns: 2
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 5

        Rectangle{
            implicitHeight: 20
            color: "grey"
            Layout.columnSpan: 2
            Layout.fillWidth: true
            Text {
                color: "black"
                text: qsTr("Bed Settings")
                anchors.centerIn: parent.Center
            }
        }

        Text{
            text: qsTr("Area X:")
            color: "grey"
        }
        MTextInput{

        }

        Text{
            text: qsTr("Area Y:")
            color: "grey"
        }
        MTextInput{

        }

        Text{
            text: qsTr("Area Z:")
            color: "grey"
        }
        MTextInput{

        }

        Text{
            text: qsTr("Temperature(ºC):")
            color: "grey"
        }
        MTextInput{

        }
    }
}

