import QtQuick
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import "." as App

ApplicationWindow {
    id: window
    width: 400
    height: width *29/20
    visible: true
    title: qsTr("Chat Room")

    Shortcut {
        sequences: ["Del","Back"]
        enabled: true
        onActivated: clearBtn.clicked()
    }

    // noName Dialog /////////////////////////////
    Dialog {
        id: noNameDialog
        x: Math.round((window.width - width) / 2)
        y: Math.round(window.height / 6)
        title: qsTr("Enter a name first")
        modal: true
        closePolicy: Popup.CloseOnEscape
        standardButtons: Dialog.Ok
        onAccepted: {
            if(name2Field.text !== "") {
                Communicator.name = name2Field.text
                noNameDialog.close()
            }
        }

        contentItem: ColumnLayout {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 40

            RowLayout {
                spacing: 10
                Layout.alignment: Qt.AlignCenter
                Label{
                    text: qsTr("Name")
                }
                TextField{
                    id: name2Field
                    focus: true
                    placeholderText: "Enter your name"
                    Keys.onReturnPressed:{
                        noNameDialog.accept()
                    }
                }
            }
        }
    }

    // SETTING DIALOG ////////////////////////////
    Dialog {
        id: settingsDialog
        x: Math.round((window.width - width) / 2)
        y: Math.round(window.height / 6)
        modal: true
        focus: true
        title: qsTr("Settings")
        closePolicy: Popup.CloseOnEscape

        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            Communicator.port = portField.text === "" ? Communicator.port : portField.text
            Communicator.name = nameField.text === "" ? Communicator.name : nameField.text

            if(!serverCheckBox.checked)
                Communicator.ip = ipField.text === "" ? Communicator.ip : ipField.text

            settingsDialog.close()
        }
        onRejected: {
            settingsDialog.close()
        }

        Component.onCompleted: {
            localHostCheckBox.checked = true
        }


        contentItem: ColumnLayout {
            id: settingsColumn
            spacing: 20

            RowLayout {
                spacing: 10

                ColumnLayout{
                    Label{
                        text: qsTr("Name")
                    }
                    Label {
                        text: qsTr("ip:")
                    }
                    Label {
                        text: qsTr("port:")
                    }
                }
                ColumnLayout{
                    TextField{
                        id: nameField
                        focus: true
                        placeholderText: "Enter your name"
                        Keys.onReturnPressed:{
                            settingsDialog.accept()
                        }
                    }

                    TextField{
                        id: ipField
                        placeholderText: "Enter ip"
                        text: "127.0.0.1"
                        validator: RegularExpressionValidator {
                            regularExpression: /^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/
                        }
                        Keys.onReturnPressed:{
                            settingsDialog.accept()
                        }
                    }
                    TextField{
                        id: portField
                        placeholderText: "Enter Port"
                        text: "9009"
                        validator: RegularExpressionValidator {
                            regularExpression: /^([0-9]{1,5})$/
                        }
                        onTextChanged: {
                            if (portField.text !== "" && (portField.text < 0 || portField.text > 65535)) {
                                portField.text = ""
                            }
                        }
                        Keys.onReturnPressed:{
                            settingsDialog.accept()
                        }
                    }
                }
            }
            CheckBox {
                id: serverCheckBox
                text: qsTr("this device is the server")
                Layout.fillWidth: true
                onCheckedChanged:
                {
                    if(checked){
                        localHostCheckBox.checked = false
                        localHostCheckBox.enabled = false
                        ipField.color = "darkgrey"
                        ipField.text = "Any ip"
                        ipField.readOnly = true
                    }
                    else{
                        ipField.readOnly = false
                        ipField.text = ""
                        ipField.color = "black"
                        localHostCheckBox.enabled = true
                    }
                }
            }
            CheckBox {
                id: localHostCheckBox
                text: qsTr("Local Host")
                Layout.fillWidth: true
                onCheckedChanged:
                {
                    if(checked){
                        ipField.readOnly = true
                        ipField.color = "darkgrey"
                        ipField.text = "127.0.0.1"
                    }
                    else{
                        ipField.readOnly = false
                        ipField.color = "black"
                    }
                }
            }

        }
    }


    Shortcut {
        sequence: "Menu"
        onActivated: optionsMenuAction.trigger()
    }

    Action {
        id: optionsMenuAction
        icon.name: "menu"
        onTriggered: optionsMenu.open()
    }

    header: ToolBar {
        RowLayout{
            spacing: 20
            anchors.fill: parent

            Label {
                id: status
                text: Communicator.status
                font.pixelSize: 15
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                icon.source: "icons/menu.png"
                action: optionsMenuAction

                Menu {
                    id: optionsMenu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight

                    Action {
                        text: qsTr("Settings")
                        onTriggered: settingsDialog.open()
                    }
                    Action {
                        text: qsTr("Disconnect")
                        onTriggered: Communicator.disconnect()
                    }
                    Action {
                        text: qsTr("Clear History")
                        onTriggered: Communicator.clearHistory()
                    }
                    Action {
                        text: qsTr("Quit")
                        onTriggered: Qt.quit()
                    }
                }
            }
        }
    }

    Column{
        id: column
        topPadding: 20
        leftPadding: 20
        rightPadding: 20
        bottomPadding: 20

        spacing: 8
        ScrollView {
            width: 360
            height: width
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            // to make the scrollBar interactive with touch
            ScrollBar.vertical.interactive: true
            wheelEnabled: true

            Flickable {
                id: flickable
                width: 360
                height: width
                contentWidth: display.width
                contentHeight: display.paintedHeight

                TextArea {
                    id: display
                    width: 360
                    height: (paintedHeight < 350 ? 350 : paintedHeight) + 8
                    readOnly: true
                    wrapMode: TextArea.Wrap
                    text: Communicator.history
                    focus: true
                }

                onContentHeightChanged: {
                    contentY = contentHeight > flickable.height ?  contentHeight - flickable.height : 0
                    // contentY = contentHeight - height
                }
            }
        }
        TextField{
            id: text
            leftPadding: 10
            width: display.width
            height: 45
            placeholderText: "Message"
            font.pixelSize: 14
            focusPolicy: Qt.WheelFocus
            text: Communicator.message

            Keys.onReturnPressed: {
                if(sendBtn.enabled)
                    sendBtn.clicked()
            }
            onTextChanged: {
                Communicator.message = text.text
                if(text.text === "")
                    clearBtn.enabled= false
                else
                    clearBtn.enabled= true

            }
        }

        Row{
            id: row
            spacing: 15

            Button{
                id: clearBtn
                width: (text.width -15) /2
                height: 35
                enabled: false
                text: "Clear"
                hoverEnabled: true
                ToolTip.timeout: 5000
                ToolTip.visible: clearBtn.enabled && hovered
                ToolTip.delay: 800
                ToolTip.text: qsTr("clear the text")
                onClicked: text.text = ""
            }
            Button{
                id: sendBtn
                width: (text.width -15) /2
                height: 35
                enabled: Communicator.status === "Connected" && clearBtn.enabled
                text: "Send"
                hoverEnabled: true
                ToolTip.timeout: 5000
                ToolTip.visible: sendBtn.enabled && hovered
                ToolTip.delay: 1000
                ToolTip.text: qsTr("(Enter)")
                onClicked: {

                    if(Communicator.name !== "") {
                        Communicator.send()
                        clearBtn.clicked()
                    }
                    else {
                        noNameDialog.open()
                    }
                }
            }
        }
        Row{
            spacing: 15
            Button{
                id: connectBtn
                width: (text.width -15) /2
                height: 35
                text: "Connect"
                hoverEnabled: true
                ToolTip.timeout: 5000
                ToolTip.visible: hovered
                ToolTip.delay: 800
                ToolTip.text: qsTr("connect to a server")
                onClicked: {
                    Communicator.connectTcp()
                }
            }
            Button{
                width: (text.width -15) /2
                height: 35
                text: "Start server"
                hoverEnabled: true
                ToolTip.timeout: 5000
                ToolTip.visible: hovered
                ToolTip.delay: 800
                ToolTip.text: qsTr("start the server and wait for connections")
                onClicked: {
                    Communicator.waitForConnection()
                }
            }
        }

    }
}




