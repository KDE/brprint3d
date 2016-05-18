import QtQuick.Layouts 1.0
import QtQuick.Window 2.1
import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

ApplicationWindow{
    id: mainWindow
    visible: true
    color: "white"
    title: "Br-Print3D"
    width: Screen.width
    height: Screen.height

    menuBar: MenuBar{
        Menu{
            title: qsTr("File")
            MenuItem {
                    text: qsTr("Open Gcode")
                    action: fileOpenAction
            }
            MenuItem {text: qsTr("Close")}
        }

        Menu{
            title: qsTr("Language")
            MenuItem {text: qsTr("English")}
            MenuItem {text: qsTr("Portuguese")}
        }

        Menu{
            title: qsTr("About")
            MenuItem {text: qsTr("Br-Print3D")}
            MenuItem {text: qsTr("KDE")}
            MenuItem {text: qsTr("How to Contribute")}
        }

        Menu{
            title: qsTr("Help")
            MenuItem {text: qsTr("Documentation")}
        }
    }
    toolBar: MToolBar{}

    Rectangle{
        id: recBackground
        width: Screen.width /10
        height: Screen.height
        color: "grey"

        Column{
            id: settingsColumn
            spacing: 2

            Rectangle{
                width: settingsColumn.width
                height: title.height +2
                Text {
                    id: title
                    text: qsTr("Br-Print3D")
                    horizontalAlignment: parent.Center
                }
             }

            SettingsButton{
                id: connectionSettings
                text: qsTr("Connection \n Settings")
                onClicked: generalLoader.setSource("qrc:/base/qml-files/ConnectionSettings.qml")
            }

            SettingsButton{
                id: bedSettings
                text: qsTr("Bed \n Settings")
                onClicked: generalLoader.setSource("qrc:/base/qml-files/BedSettings.qml")
            }

            SettingsButton{
                id: extruderSettings
                text: qsTr("Extruder \n Settings")
                onClicked: generalLoader.setSource("qrc:/base/qml-files/ExtruderSettings.qml")
            }

            SettingsButton{
                id: gcodeEditor
                text: qsTr("GCode Editor")
                onClicked: generalLoader.setSource("qrc:/base/qml-files/GCodeEditor.qml")
            }
        }
    }

    Action {
        id: fileOpenAction
        text: "Open"
        onTriggered: {
            fileDialog.selectExisting = true
            fileDialog.open()
        }
    }

    Loader{
         id: generalLoader
         anchors.left: recBackground.right
         anchors.top: recBackground.top
    }

    FileDialog{
        id: fileDialog
        title: qsTr("Select a Gcode file:")
        folder: shortcuts.home
        nameFilters: [ "GCode Files (*.gcode *.gco)" ]
    }
}

