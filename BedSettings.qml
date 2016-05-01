import QtQuick 2.0
import QtQuick.Window 2.2

Rectangle{

    id: bedSet
    color: "black"
    width: Screen.width /4
    height: Screen.height
    Column{
        spacing: 5
        Rectangle{
            width: bedSet.width
            height: 20
            color: "gray"
            Text {
                color: "black"
                text: qsTr("Bed Settings")
                anchors.centerIn: parent.Center
            }
        }

        Row{
            spacing: 10
            Text{
                text: qsTr("Area X:")
                color: "grey"
            }
            MTextInput{

            }
        }
        Row{
            spacing: 10
            Text{
                text: qsTr("Area Y:")
                color: "grey"
            }
            MTextInput{

            }
        }
        Row{
            spacing: 10
            Text{
                text: qsTr("Area Z:")
                color: "grey"
            }
            MTextInput{

            }
        }
        Row{
            spacing: 10
            Text{
                text: qsTr("Temperature(ºC):")
                color: "grey"
            }
            MTextInput{

            }
        }
    }

}
