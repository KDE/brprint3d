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

    id: connectionSet
    color: "#31363b"
    property color mtextColor: "#eff0f1"
    anchors.rightMargin: 3

    Rectangle{
        id: title
        color: mtextColor
        width: parent.width
        height: tex.height
        Text{
            id: tex
            text: qsTr("Connection Settings")
            color: "#31363b"
        }
    }

    GridLayout{
        columns: 2
        anchors.top: title.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 5

        Text {
            text: qsTr("Serial Port:")
            color: mtextColor
        }
        //How to set a extern list?
        ComboBox{
            id: cbSerialPorts
            Layout.minimumWidth: cbTransmitionRate.width
            model: []
            style: ComboBoxStyle{
                textColor: mtextColor
            }
        }

        Text {
            text: qsTr("Transmition Rate:")
            color: "#eff0f1"
        }
        ComboBox{
            id: cbTransmitionRate
            Text {
                text: "115200"
                id: placeholder
                visible: false
            }
            Layout.minimumWidth: placeholder.width + 50
            model: [115200,4800,9600,19200,38400,57600]
            style: ComboBoxStyle{
                textColor: mtextColor
            }
        }

        Text {
            text: qsTr("Cache Size:")
            color: mtextColor
        }

        TextField{
            textColor: "#eff0f1"
            inputMask: "999"
            activeFocusOnPress: true
            validator: IntValidator{}
            text: "127"
        }
        Text{
            text: qsTr("Reset on Connect:")
            color: mtextColor
        }
        CheckBox{
            id: resetOnConnect
        }
        Text{
            text: qsTr("Job Log:")
            color: mtextColor
        }
        CheckBox{
            id: printLog
        }
    }
}

