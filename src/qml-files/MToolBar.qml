import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

ToolBar{
    width: Screen.width

    RowLayout{
        anchors.fill: parent
        spacing: 5

        ToolButton{ action: openFileAction }

        ToolButton{ action: connectAction  }

        Item { Layout.fillWidth: true }

        ToolButton{
            action: startAction
            Layout.alignment: Qt.AlignRight
        }

        ToolButton{
            action: pauseAction
            Layout.alignment: Qt.AlignRight
        }

        ToolButton{
            action: stopAction
            Layout.alignment: Qt.AlignRight
        }

        ToolButton{
            action: emergencyStop
            Layout.alignment: Qt.AlignRight
        }

    }

    Action{
    id: openFileAction
    text: qsTr("Open GCode")
    }

    Action{
    id: connectAction
    text: qsTr("Connect")
    }

    Action{
    id: startAction
    text: qsTr("Start")
    }

    Action{
    id: pauseAction
    text: qsTr("Pause")
    }

    Action{
    id: stopAction
    text: qsTr("Stop")
    }

    Action{
    id: emergencyStop
    text: qsTr("Emergency Stop")
    }
}
