import QtQuick
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Server")


    TextField {
        id: displayArea
        x: 85
        y: 100
        width: 450
        height: 35
        rightPadding: 10
        font.pixelSize: 30
        horizontalAlignment: Text.AlignRight
        text: Reciever.display
    }

    Button{
        id: connectButton
        width: 60
        height: 30
        text: "Connect"
        onClicked: {

        }
    }

    Button{
        x: displayArea.x + displayArea.width/2 - width/2
        y: displayArea.y + displayArea.height + 8
        id: sendButton
        width: 60
        height: 30
        text: "Send"
        enabled: false
        onClicked: {
            displayArea.text.t += 1
        }
    }

}
