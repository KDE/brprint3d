import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Rectangle{

    id: connectionSet
    color: "black"
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
                anchors.centerIn: parent
                color: "black"
                text: qsTr("Connection Settings")
            }
        }
        Text {
            text: qsTr("Serial Port:")
            color: "grey"
        }
        //How to set a extern list?
        ComboBox{
            id: cbSerialPorts
            Layout.minimumWidth: cbTransmitionRate.width
            model: []
            style: ComboBoxStyle{
                textColor: "black"
            }
        }

        Text {
            text: qsTr("Transmition Rate:")
            color: "grey"
        }
        ComboBox{
            id: cbTransmitionRate
            Text {
                text: "115200"
                id: placeholder
                visible: false
            }
            Layout.minimumWidth: placeholder.width + 50
            model: [115200,4800,9600,19200,38400,57600]
            style: ComboBoxStyle{
                textColor: "black"
            }
        }

        Text {
            text: qsTr("Cache Size:")
            color: "grey"
        }

        TextInput{
            text: "127"
            color: "grey"
            inputMask: "000;_"
            validator: IntValidator{}
        }
        Text{
            text: qsTr("Reset on Connect:")
            color: "grey"
        }
        CheckBox{
            id: resetOnConnect
        }
        Text{
            text: qsTr("Job Log:")
            color: "grey"
        }
        CheckBox{
            id: printLog
        }
    }
}

