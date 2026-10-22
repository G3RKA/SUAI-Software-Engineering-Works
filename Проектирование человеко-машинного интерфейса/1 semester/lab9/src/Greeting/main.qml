import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 320
    height: 180
    visible: true
    title: "Приветствие"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 10

        TextField {
            id: nameField
            Layout.fillWidth: true
            placeholderText: "Введите имя"
        }

        Button {
            Layout.fillWidth: true
            text: "Поздороваться"
            onClicked: greeting.text = nameField.text === ""
                       ? "Введите имя"
                       : "Привет, " + nameField.text + "!"
        }

        Text {
            id: greeting
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 18
            font.bold: true
            text: ""
        }
    }
}
