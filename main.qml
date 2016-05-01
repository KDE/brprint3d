import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

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
            MenuItem {text: qsTr("Open Gcode")}
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
    toolBar: Loader{ source: Qt.resolvedUrl("qrc:/base/MToolBar.qml") }

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
                onClicked: generalLoader.setSource("qrc:/base/ConnectionSettings.qml")
            }

            SettingsButton{
                id: bedSettings
                text: qsTr("Bed \n Settings")
                onClicked: generalLoader.setSource("qrc:/base/BedSettings.qml")
            }

            SettingsButton{
                id: extruderSettings
                text: qsTr("Extruder \n Settings")
                onClicked: generalLoader.setSource("qrc:/base/ExtruderSettings.qml")
            }

            SettingsButton{
                id: gcodeEditor
                text: qsTr("GCode Editor")
                onClicked: generalLoader.setSource("")
            }
        }
    }

    Loader{
         id: generalLoader
         anchors.left: recBackground.right
         anchors.top: recBackground.top
    }
}

