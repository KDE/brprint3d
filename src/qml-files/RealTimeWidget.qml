/*=====================================================================

 BRPrint3D, Open Source 3D Printing Host

 Copyright (C) 2016 BRPrint3D Authors

 This file is part of the BRPrint3D project

 BRPrint3D is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 BRPrint3D is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with BRPrint3D. If not, see <http://www.gnu.org/licenses/>.

 ======================================================================*/
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
