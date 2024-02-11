import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import models 1.0

Item
{
	height: startButton.height
	RowLayout	{
    Button {
      id: startButton
      text: "Start"
      onClicked: ScreenSaver.start()
    }

    Button {
      text: "Stop"
      onClicked: ScreenSaver.stop()
    }

    Button {
      text: "Take shot"
      onClicked: ScreenSaver.takeNewRecord()
    }
  }
}