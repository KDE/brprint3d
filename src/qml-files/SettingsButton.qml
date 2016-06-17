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

import QtQuick 2.5
import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Rectangle{
    id: root
    property color buttonColor: "transparent"
    property color onHoverColor: "#31363b"
    property color onClickedColor: "#3daee9"//"#1cdc9a" Green
    property alias text: label.text
    property alias source: icon.source
    property bool clickControl: false
    signal clicked

    anchors.left: parent.left
    anchors.right: parent.right

    height: Screen.height /8
    ColumnLayout{
        anchors.fill: parent
        Image {
            id: icon
            width: parent.width /2
            height: parent.height /1.5
        }

        Text {
            id: label
            Layout.alignment: Qt.AlignCenter
            color: "white"
            text: qsTr("a")
        }
    }

    MouseArea{
        id: mArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            root.clicked()
        }
    }

    color: mArea.containsMouse ? onHoverColor : clickControl ? onClickedColor : buttonColor
}
