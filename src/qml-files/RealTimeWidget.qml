import QtQuick 2.0
import QtQuick.Window 2.1

Rectangle{

    id: root
    property color textColor: "#eff0f1"
    color: "#31363b"
    width: parent.width/9
    height: parent.height

    Column{
        spacing: 10
        Text{
            text: qsTr("Real Time Informations:")
            color: textColor
        }
        Text{
            text: qsTr("Bed \nTemperature(ºC)")
            color: textColor
        }

        Text{
            text: qsTr("T")
            color: textColor
        }
        //TODO: If use more then one extruder use a Repeater
        Text{
            text: qsTr("Extruder(s) \nTemperature(ºC)")
            color: textColor
        }

        Text{
            text: qsTr("T")
            color: textColor
        }
    }
}
