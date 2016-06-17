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
import QtQuick.Controls.Styles 1.4

Rectangle{
    id: root
    color: "#31363b"
    width: parent.width
    property color textColor: "#eff0f1"
    anchors.rightMargin: 3

    Rectangle{
        id: title
        color: textColor
        width: parent.width
        height: tex.height
        Text{
            id: tex
            text: qsTr("Filament Settings")
            color: "#31363b"
        }
    }

        GridLayout{
            columns: 2
            rowSpacing: 5
            anchors.top: title.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5

            Text{
                text: qsTr("Filament Size: ")
            }

            TextField{
                id: filamentSize
                activeFocusOnPress: true
                validator: DoubleValidator{}
                text: "1.75"
            }

            Text{
                text: qsTr("Materials:")
            }

            ComboBox{
                model: ["PLA", "ABS", "PET","Wood PLA"]
                Layout.minimumWidth: filamentSize.width
                style: ComboBoxStyle{
                    textColor: textColor

                }
            }

            Text{
                text: qsTr("Filament Controls")
                color: textColor
                Layout.columnSpan: 2
                Layout.alignment: Qt.AlignHCenter
            }

            Button{
                id: fillRetract
                text: qsTr("Retract")
                Layout.columnSpan: 2
                Layout.alignment: Qt.AlignHCenter
            }

            Button{
                id: fillFowardSlow
                text: qsTr("Foward Slow")
            }
            Button{
                id: fillFowardFast
                text: qsTr("Foward Fast")
                Layout.alignment: Qt.AlignRight
            }
        }
}
