import QtQuick 2.5
import QtQuick.Controls 1.4
import brprint3d 1.0
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

Rectangle{
    id: root
    width: parent.width
    color: "#31363b"

    ColumnLayout{
        spacing: 2
        anchors.fill: parent
        anchors.margins: 3

        Text {
            text: qsTr("GCode Header")
            Layout.fillWidth: true
            color: "#eff0f1"
        }

        TextArea{
            id: gcodeHeader
            Layout.fillWidth: true
            Layout.fillHeight: true
            focus:  true
            wrapMode: TextEdit.Wrap
            style: TextAreaStyle{
                backgroundColor: "#eff0f1"
                textColor:"#31363b"
            }
            text: gcodeHandler.fileContentHeader
        }

        Text {
            text: qsTr("GCode Footer")
            Layout.fillWidth: true
            color: "#eff0f1"
        }

        TextArea{
            id: gcodeFooter
            Layout.fillWidth: true
            Layout.fillHeight: true
            focus:  true
            wrapMode: TextEdit.Wrap
            style: TextAreaStyle{
                backgroundColor: "#eff0f1"
                textColor:"#31363b"
            }
            text: gcodeHandler.fileContentFooter
        }
    }
}



