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
        width: Screen.width /9.5
        height: Screen.height
        color: "#1a1a1aff"

        Column{
            id: settingsColumn
            spacing: 2

            Rectangle{
                width: recBackground.width
                height: title.height +2
                color: "transparent"
                Text {
                    id: title
                    text: qsTr("Br-Print3D")
                    horizontalAlignment: parent.Center
                }
             }

            SettingsButton{
                id: connectionSettings
                Image {
                    source: "qrc:/images/usb.png"
                    width: parent.width /2
                    height: parent.height /1.5
                    anchors.centerIn: parent
                }
                Text{
                    text: qsTr("Connection Settings")
                    color: "white"
                    anchors.bottom: parent.bottom
                }
                onClicked: generalLoader.setSource("qrc:/base/qml-files/ConnectionSettings.qml")
            }

            SettingsButton{
                id: bedSettings
                Image {
                    source: "qrc:/images/bed.png"
                    width: parent.width /2
                    height: parent.height /1.5
                    anchors.centerIn: parent
                }
                Text{
                    text: qsTr("Bed Settings")
                    color: "white"
                    anchors.bottom: parent.bottom
                }
                onClicked: generalLoader.setSource("qrc:/base/qml-files/BedSettings.qml")
            }

            SettingsButton{
                id: extruderSettings
                Image {
                    source: "qrc:/images/extruder.png"
                    width: parent.width /2.7
                    height: parent.height /1.5
                    anchors.centerIn: parent
                }
                Text {
                    text: qsTr("Extruder Settings")
                    color: "white"
                    anchors.bottom: parent.bottom
                }
                onClicked: generalLoader.setSource("qrc:/base/qml-files/ExtruderSettings.qml")
            }

            SettingsButton{
                id: gcodeEditor
                Text {
                    text: qsTr("GCode Settings")
                    color: "white"
                    anchors.bottom: parent.bottom
                }
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

