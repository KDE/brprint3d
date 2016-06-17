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
import brprint3d 1.0
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

Rectangle{
    id: root
    width: parent.width
    color: "#31363b"
    anchors.rightMargin: 3
    property color mTextColor:"#eff0f1"

    Rectangle{
        id: title
        color: mTextColor
        width: parent.width
        height: tex.height
        Text{
            id: tex
            text: qsTr("GCode Editor")
            color: "#31363b"
        }
    }

    ColumnLayout{
        spacing: 2
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: title.bottom
        anchors.bottom: parent.bottom
        anchors.margins: 3

        Text {
            text: qsTr("Header")
            Layout.fillWidth: true
            color: mTextColor
        }

        TextArea{
            id: gcodeHeader
            Layout.fillWidth: true
            Layout.fillHeight: true
            focus:  true
            wrapMode: TextEdit.Wrap
            style: TextAreaStyle{
                backgroundColor: mTextColor
                textColor:"#31363b"
            }
            text: gcodeHandler.fileContentHeader
        }

        Text {
            text: qsTr("Footer")
            Layout.fillWidth: true
            color: mTextColor
        }

        TextArea{
            id: gcodeFooter
            Layout.fillWidth: true
            Layout.fillHeight: true
            focus:  true
            wrapMode: TextEdit.Wrap
            style: TextAreaStyle{
                backgroundColor: mTextColor
                textColor:"#31363b"
            }
            text: gcodeHandler.fileContentFooter
        }
    }
}



