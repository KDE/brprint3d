import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Rectangle{

    id: extruderSet
    color: "black"
    width: Screen.width /4
    height: Screen.height
    GridLayout{
        id: grid
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
                text: qsTr("Extruders Settings")
                anchors.centerIn: parent.Center
            }
        }
        Text {
            text: qsTr("Extruder:")
            color: "grey"
        }
        //How to set a extern list? use a radiobutton instead??
        ComboBox{
            id: cbExtrudersQnt
            model: [1]
            style: ComboBoxStyle{
                textColor: "black"
            }
        }

        Text{
            text: qsTr("Temperature(ºC):")
            color: "grey"
        }
        MTextInput{

        }
        Text{
            text: qsTr("Moviment Speed(mm/s):")
            color: "grey"
        }
        MTextInput{

        }
        Text{
            text: qsTr("Extrusion Speed(mm/s):")
            color: "grey"
        }
        MTextInput{

        }
        Text{
            text: qsTr("Fan Speed(%):")
            color: "grey"
        }
        TextInput{
            inputMask: "000%;_"
            color: "white"
        }
    }

    GroupBox{
        id: groupbox
        title: qsTr("MAX TEMPERATURES")
        flat: true
        anchors.top: grid.bottom
        Column{
            spacing: 5

            Rectangle{
                border.color: "red"
                border.width: 1
                width: info.width +10
                height: info.height +10
                color: "black"
                Text {
                    id: info
                    text: qsTr(" Please, don't forget to add here the maximum \n temperature that your extruder have. This is\n for your safety and of the 3DPrinter.")
                    color: "grey"
                    horizontalAlignment: Text.Center
                }
            }
        }
    }

    GridLayout{
        columns: 2
        anchors.top: groupbox.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5
        Text{
            text: qsTr("Max Temperature(ºC):")
            color: "grey"
        }
        MTextInput{

        }
    }
}

