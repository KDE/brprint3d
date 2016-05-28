import QtQuick 2.0
import QtQuick.Window 2.1

Rectangle{

    id: root
    color: "#1a1a1aff"
    width: Screen.width /9
    height: Screen.height

    Column{
        spacing: 10
        Text{
            text: qsTr("Real Time Informations:")
        }
        Text{
            text: qsTr("Bed \nTemperature(ºC)")
        }

        Text{
            text: qsTr("T")
        }
        //TODO: If use more then one extruder use a Repeater
        Text{
            text: qsTr("Extruder(s) \nTemperature(ºC)")
        }

        Text{
            text: qsTr("T")
        }
    }
}
