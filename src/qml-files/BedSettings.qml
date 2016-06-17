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
    anchors.rightMargin: 3

    Rectangle{
        id: title
        color: textColor
        width: parent.width
        height: tex.height
        Text{
            id: tex
            text: qsTr("Bed Settings")
            color: "#31363b"
        }
    }

        GridLayout{
        columns: 3
        anchors.top: title.bottom
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

