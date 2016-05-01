import QtQuick 2.5

Rectangle{
    color: "gray"
    width: areaX.width + 10
    height: 20

    TextInput{
        id: areaX
        color: "white"
        validator: DoubleValidator{}
        inputMask: "0999.000;_"
        onFocusChanged: true ? {cursorVisible: true} : {cursorVisible: false}
    }
}
