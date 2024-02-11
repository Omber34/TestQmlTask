import QtQuick 2.12
import QtQuick.Window 2.12

Window
{
    id: window

    visible: true

    minimumWidth: Constants.previewImageWidth * 3
    minimumHeight: Constants.gridCellHeight * 3


    title: "ScreenSaver"

    color: "white"

		StartScreen {
        anchors.fill: parent
    }
}
