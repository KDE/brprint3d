import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

Rectangle{
    id: bedSet
    color: "#31363b"
    width: parent.width
    property bool heatedBed: true
    property color textColor: "#eff0f1"

        GridLayout{
        columns: 3
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5
        enabled: heatedBed ? true : false

        Text{
            text: qsTr("Area X:")
            color: textColor
        }

        TextField{
            textColor: bedSet.textColor
            activeFocusOnPress: true
            validator: IntValidator{bottom:100}
            text: "200"
        }
        Text {
            text: qsTr("mm")
            color: textColor
        }

        Text{
            text: qsTr("Area Y:")
            color: textColor
        }
        TextField{
            textColor: bedSet.textColor
            activeFocusOnPress: true
            validator: IntValidator{bottom:100}
            text: "200"
        }
        Text {
            text: qsTr("mm")
            color: textColor
        }

        Text{
            text: qsTr("Area Z:")
            color: textColor
        }
        TextField{
            textColor: bedSet.textColor
            activeFocusOnPress: true
            validator: IntValidator{bottom:100}
            text: "200"
        }
        Text {
            text: qsTr("mm")
            color: textColor
        }

        Text{
            text: qsTr("Temperature:")
            color: textColor
        }
        TextField{
            textColor: bedSet.textColor
            activeFocusOnPress: true
            validator: IntValidator{bottom: 0; top: 130}
            text: "110"
        }
        Text {
            text: qsTr("ºC")
            color: textColor
        }
    }
}

