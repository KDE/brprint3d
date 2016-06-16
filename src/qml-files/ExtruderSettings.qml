import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Rectangle{

    id: extruderSet
    color: "#31363b"
    width: Screen.width /4
    height: Screen.height
    GridLayout{
        id: grid
        columns: 3
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 5

        Text {
            text: qsTr("Extruder:")
            color: "#eff0f1"
        }
        //How to set a extern list? use a radiobutton instead??
        ComboBox{
            id: cbExtrudersQnt
            model: [1]
            style: ComboBoxStyle{
                textColor: "#eff0f1"
            }
        }
        Text{

        }

        Text{
            text: qsTr("Temperature:")
            color: "#eff0f1"
        }
        MTextInput{

        }
        Text{
            text: qsTr("ºC")
            color: "#eff0f1"
        }
        Text{
            text: qsTr("Moviment Speed:")
            color: "#eff0f1"
        }
        MTextInput{

        }
        Text{
            text: qsTr("mm/s")
            color: "#eff0f1"
        }
        Text{
            text: qsTr("Extrusion Speed(mm/s):")
            color: "#eff0f1"
        }
        MTextInput{

        }
        Text{
            text: qsTr("mm/s")
            color: "#eff0f1"
        }
        Text{
            text: qsTr("Fan Speed:")
            color: "#eff0f1"
        }
        TextField{
            textColor: "#eff0f1"
            inputMask: "000"
            activeFocusOnPress: true
            validator: IntValidator{}
            text: "100"
        }
        Text{
            text: qsTr("%")
            color: "#eff0f1"
        }

        Text{
            id: warning
            text: ">>Important<<"
            color: "#ed1515"
            Layout.columnSpan: 3
        }

        Text {
            id: info
            anchors.margins: 5
            Layout.columnSpan: 3
            text: qsTr(" Please, don't forget to add here the maximum \n temperature that your extruder have. This is\n for your safety and of the 3DPrinter.")
            color: "#eff0f1"
            horizontalAlignment: Text.Center
        }

        Text{
            text: qsTr("Max Temperature:")
            color: "#ed1515"
        }
        MTextInput{

        }
        Text{
            text: qsTr("ºC")
            color: "#eff0f1"
        }

    }
}
