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
}

