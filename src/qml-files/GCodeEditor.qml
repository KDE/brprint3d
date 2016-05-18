import QtQuick 2.0
import QtQuick.Controls 1.2
import brprint3d 1.0
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Rectangle{

    Text {
        text: qsTr("GCode Editor")
        color: "white"
    }

    Flickable {
        id: flick
        clip: true
        width: Screen.width /4
        height: Screen.height

        TextEdit{
            id: gcodeArea
            width: flick.width
            height: flick.height
            focus:  true
            wrapMode: TextEdit.Wrap

            text: gcodeHandler.fileContent
        }
    }
    GcodeHandler{
        id: gcodeHandler
        target: gcodeArea

    }
}



