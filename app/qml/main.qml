import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Templates 2.12 as T
import QtQuick.Layouts 1.10

Window
{
    id: window

    visible: true
    width: 800
    height: 600

    title: qsTr("TetrisGame")

    color: "black"

    T.StackView
    {
        id: stackView
        z: 5
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        height: parent.height
        clip: true

        background: Rectangle
        {
            anchors.fill: parent
            color: "#33000000"
        }

        initialItem: StartScreen {}

        popEnter: Transition {}
        popExit: Transition {}
        pushEnter: Transition {}
        pushExit: Transition {}
        replaceEnter: Transition {}
        replaceExit: Transition {}
    }

}
