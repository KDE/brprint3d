import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2

Rectangle{

    id: connectionSet
    color: "black"
    width: Screen.width /4
    height: Screen.height
    Column{
        spacing: 5
        Rectangle{
            width: connectionSet.width
            height: 20
            color: "grey"
            Text {
                color: "black"
                text: qsTr("Connection Settings")
            }
        }

        Row{
            spacing: 10
            Text {
                text: qsTr("Serial Port:")
                color: "grey"
            }
            //How to set a extern list?
            ComboBox{
                id: cbSerialPorts
                model: []
                style: ComboBoxStyle{
                    textColor: "black"
                }
            }
       }
        Row{
            spacing: 10
            Text {
                text: qsTr("Serial Port:")
                color: "grey"
            }
            ComboBox{

                model: [115200,4800,9600,19200,38400,57600]
                style: ComboBoxStyle{
                    textColor: "black"
                }
            }
       }
        Row{
            spacing: 10
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
       }
        Row{
            spacing:10
            Text{
                text: qsTr("Reset on Connect:")
                color: "grey"
            }
            CheckBox{
                id: resetOnConnect
            }
        }
        Row{
            spacing:10
            Text{
                text: qsTr("Job Log:")
                color: "grey"
            }
            CheckBox{
                id: printLog
            }
        }
    }

}
