import QtQuick
import QtQuick.Controls 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Client")

    TextField {
        id: displayArea
        x: 85
        y: 100
        width: 450
        height: 35
        rightPadding: 10
        font.pixelSize: 30
        horizontalAlignment: Text.AlignRight
        text: Sender.number
        onTextChanged:{
            Sender.number = text
            Sender.sendButtonClicked()
        }
    }

    Button{
        x: displayArea.x + displayArea.width/2 - width/2
        y: displayArea.y + displayArea.height + 8
        id: sendButton
        width: 60
        height: 30
        text: "Send"
        // enabled: false
        onClicked: {
            Sender.sendButtonClicked()
        }
    }

    Button{
        x: displayArea.x + displayArea.width/2 - width/2
        y: displayArea.y + displayArea.height + 46
        id: connectButton
        width: 60
        height: 30
        text: "Connect"
        // enabled: false
        onClicked: {
            Sender.connectTCP()
            connectButton.enabled = false
        }
    }
    Button{
        x: displayArea.x + displayArea.width/2 - width/2
        y: displayArea.y + displayArea.height + 84
        id: disconnectButton
        width: 60
        height: 30
        text: "disConnect"
        // enabled: false
        onClicked: {
            connectButton.enabled = true
        }
    }

}
