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
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Rectangle{

    id: extruderSet
    color: "#31363b"
    width: Screen.width /4
    height: Screen.height
    property color mtextColor: "#eff0f1"
    anchors.rightMargin: 3

    Rectangle{
        id: title
        color: mtextColor
        width: parent.width
        height: tex.height
        Text{
            id: tex
            text: qsTr("Extruder Settings")
            color: "#31363b"
        }
    }

    GridLayout{
        id: grid
        columns: 3
        anchors.left: parent.left
        anchors.top: title.bottom
        anchors.right: parent.right
        anchors.margins: 5

        Text {
            text: qsTr("Extruder:")
            color: textColor
        }
        //How to set a extern list? use a radiobutton instead??
        ComboBox{
            id: cbExtrudersQnt
            model: [1]
            style: ComboBoxStyle{
                textColor: textColor
            }
        }

        Text{

        }

        Text{
            text: qsTr("Temperature:")
            color: textColor
        }

        TextField{
            textColor: mtextColor
            activeFocusOnPress: true
            validator: IntValidator{bottom:160;top:300}
            placeholderText: qsTr("(160~300)")
        }

        Text{
            text: qsTr("ºC")
            color: textColor
        }

        Text{
            text: qsTr("Moviment Speed:")
            color: textColor
        }

        TextField{
            textColor: mtextColor
            activeFocusOnPress: true
            validator: IntValidator{bottom:10;top:300}
            placeholderText: qsTr("(10~300)")
        }

        Text{
            text: qsTr("mm/s")
            color: textColor
        }

        Text{
            text: qsTr("Extrusion Speed:")
            color: textColor
        }

        TextField{
            textColor: mtextColor
            activeFocusOnPress: true
            validator: IntValidator{bottom:10;top:300}
            placeholderText: qsTr("(10~300)")
        }

        Text{
            text: qsTr("mm/s")
            color: textColor
        }

        Text{
            text: qsTr("Fan Speed:")
            color: textColor
        }

        TextField{
            textColor: mtextColor
            activeFocusOnPress: true
            validator: IntValidator{bottom: 0; top: 100}
            placeholderText: qsTr("(0~100)")
        }

        Text{
            text: qsTr("%")
            color: textColor
        }

        GroupBox{
            id: warning
            title: qsTr(">>Important<<")
            Layout.columnSpan: 3
            Layout.alignment: Qt.AlignHCenter

            Text {
                id: info
                anchors.margins: 5
                Layout.columnSpan: 3
                text: qsTr(" Please, don't forget to add here the maximum \n temperature that your extruder have. This is\n for your safety and of the 3DPrinter.")
                color: "#ed1515"
                horizontalAlignment: Text.Center
            }
        }

        Text{
            text: qsTr("Max Temperature:")
            color: textColor
        }
        TextField{
            textColor: mtextColor
            activeFocusOnPress: true
            validator: IntValidator{bottom:160; top:300}
            placeholderText: qsTr("(160~300)")
        }

        Text{
            text: qsTr("ºC")
            color: textColor
        }
    }
}
