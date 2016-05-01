import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

ToolBar{
    width: Screen.width

    RowLayout{
        anchors.fill: parent
        spacing: 5

        ToolButton{
            text: qsTr("Open GCode")
        }

        ToolButton{
            text: qsTr("Connect")
        }

        Item { Layout.fillWidth: true }

        ToolButton{
            text: qsTr("Start")
            Layout.alignment: Qt.AlignRight
        }

        ToolButton{
            text: qsTr("Pause")
            Layout.alignment: Qt.AlignRight
        }

        ToolButton{
            text: qsTr("Stop")
            Layout.alignment: Qt.AlignRight
        }

        ToolButton{
            text: qsTr("Emergency Stop")
            Layout.alignment: Qt.AlignRight
        }

    }
}
