import QtQuick 2.0
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

Rectangle{

    id: root
    property color textColor: "#eff0f1"
    color: "#31363b"
    width: parent.width/9
    height: parent.height
    anchors.margins: 5

    ColumnLayout{
        spacing: 10
        Layout.margins: 3
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right

        GroupBox{
            id: gbox
            title: qsTr("Controllers")
            Layout.alignment: Qt.AlignHCenter
            ColumnLayout{
                anchors.fill: parent
                Button{
                    id: heatBed
                    text: qsTr("Heat Bed")
                    Layout.alignment: Qt.AlignHCenter
                    checkable: true
                }
                Button{
                    id: heatExtruder
                    Layout.alignment: Qt.AlignHCenter
                    checkable: true
                    text: qsTr("Heat Extruder")
                }
            }
        }
        Text{
            text: qsTr("Temperatures")
            color:textColor
            Layout.alignment: Qt.AlignHCenter
        }
        Text {
            text: qsTr("T1")
            Layout.alignment: Qt.AlignHCenter
        }

        Text {
            text: qsTr("T2")
            Layout.alignment: Qt.AlignHCenter
        }
    }
}
