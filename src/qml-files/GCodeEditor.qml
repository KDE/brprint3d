import QtQuick 2.5
import QtQuick.Controls 1.2
import brprint3d 1.0
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import Qt.labs.controls 1.0

Rectangle{
    id: root
    width: Screen.width /4
    height: Screen.height
    color: "black"
    Column{
        spacing: 2

        Text {
            id: text
            text: qsTr("GCode Editor")
            color: "white"
        }
        Rectangle{
            color: "lightgrey"
            width: root.width
            height: root.height - text.height
            Flickable {
                id: flick
                clip: true
                width: Screen.width /4
                height: Screen.height
                ScrollBar.vertical: ScrollBar{
                }

                TextEdit{
                    id: gcodeArea
                    width: flick.width
                    height: flick.height
                    focus:  true
                    wrapMode: TextEdit.Wrap
                    color: "black"

                    text: gcodeHandler.fileContent
                }
            }
        }
    }
}



