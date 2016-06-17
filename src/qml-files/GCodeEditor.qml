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
    anchors.rightMargin: 3
    property color mTextColor:"#eff0f1"

    Rectangle{
        id: title
        color: mTextColor
        width: parent.width
        height: tex.height
        Text{
            id: tex
            text: qsTr("GCode Editor")
            color: "#31363b"
        }
    }

    ColumnLayout{
        spacing: 2
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: title.bottom
        anchors.bottom: parent.bottom
        anchors.margins: 3

        Text {
            text: qsTr("Header")
            Layout.fillWidth: true
            color: mTextColor
        }

        TextArea{
            id: gcodeHeader
            Layout.fillWidth: true
            Layout.fillHeight: true
            focus:  true
            wrapMode: TextEdit.Wrap
            style: TextAreaStyle{
                backgroundColor: mTextColor
                textColor:"#31363b"
            }
            text: gcodeHandler.fileContentHeader
        }

        Text {
            text: qsTr("Footer")
            Layout.fillWidth: true
            color: mTextColor
        }

        TextArea{
            id: gcodeFooter
            Layout.fillWidth: true
            Layout.fillHeight: true
            focus:  true
            wrapMode: TextEdit.Wrap
            style: TextAreaStyle{
                backgroundColor: mTextColor
                textColor:"#31363b"
            }
            text: gcodeHandler.fileContentFooter
        }
    }
}



