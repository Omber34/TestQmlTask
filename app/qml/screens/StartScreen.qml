import QtQuick 2.12
import QtQuick.Layouts 1.15
import models 1.0

Item
{
		ScreenSaver
		{
			id: saver
			model: mainModel
		}

		SaverControlPanel
		{
			screenSaver: saver
		  id: controlPanel
		}

		RecordModel
		{
			id: mainModel
		}

		Rectangle
		{
      anchors.top: controlPanel.bottom
      anchors.right: parent.right
      anchors.left: parent.left
      anchors.bottom: parent.bottom
			RecordView
      {
        anchors.fill: parent
				model: mainModel
      }
		}

}
