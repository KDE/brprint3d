import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3


Rectangle{

    id: connectionSet
    color: "#31363b"
    GridLayout{
        columns: 2
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 5

        Text {
            text: qsTr("Serial Port:")
            color: "#eff0f1"
        }
        //How to set a extern list?
        ComboBox{
            id: cbSerialPorts
            Layout.minimumWidth: cbTransmitionRate.width
            model: []
            style: ComboBoxStyle{
                textColor: "#eff0f1"
            }
        }

        Text {
            text: qsTr("Transmition Rate:")
            color: "#eff0f1"
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
                textColor: "#31363b"
            }
        }

        Text {
            text: qsTr("Cache Size:")
            color: "#eff0f1"
        }

        TextField{
            textColor: "#eff0f1"
            inputMask: "999"
            activeFocusOnPress: true
            validator: IntValidator{}
            text: "127"
        }
        Text{
            text: qsTr("Reset on Connect:")
            color: "#eff0f1"
        }
        CheckBox{
            id: resetOnConnect
        }
        Text{
            text: qsTr("Job Log:")
            color: "#eff0f1"
        }
        CheckBox{
            id: printLog
        }
    }
}

