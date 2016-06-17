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
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

Rectangle{
    id: bedSet
    color: "#31363b"
    width: parent.width
    property bool heatedBed: true
    property color textColor: "#eff0f1"
    anchors.rightMargin: 3

    Rectangle{
        id: title
        color: textColor
        width: parent.width
        height: tex.height
        Text{
            id: tex
            text: qsTr("Bed Settings")
            color: "#31363b"
        }
    }

        GridLayout{
        columns: 3
        anchors.top: title.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5
        enabled: heatedBed ? true : false



        Text{
            text: qsTr("Area X:")
            color: textColor
        }

        TextField{
            textColor: bedSet.textColor
            activeFocusOnPress: true
            validator: IntValidator{bottom:100}
            text: "200"
        }
        Text {
            text: qsTr("mm")
            color: textColor
        }

        Text{
            text: qsTr("Area Y:")
            color: textColor
        }
        TextField{
            textColor: bedSet.textColor
            activeFocusOnPress: true
            validator: IntValidator{bottom:100}
            text: "200"
        }
        Text {
            text: qsTr("mm")
            color: textColor
        }

        Text{
            text: qsTr("Area Z:")
            color: textColor
        }
        TextField{
            textColor: bedSet.textColor
            activeFocusOnPress: true
            validator: IntValidator{bottom:100}
            text: "200"
        }
        Text {
            text: qsTr("mm")
            color: textColor
        }

        Text{
            text: qsTr("Temperature:")
            color: textColor
        }
        TextField{
            textColor: bedSet.textColor
            activeFocusOnPress: true
            validator: IntValidator{bottom: 0; top: 130}
            text: "110"
        }
        Text {
            text: qsTr("ºC")
            color: textColor
        }
    }
}

