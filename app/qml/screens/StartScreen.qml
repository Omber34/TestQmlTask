import QtQuick 2.12
import QtQuick.Layouts 1.15
import models 1.0

Item
{
		SaverControlPanel
		{
		  id: controlPanel
		}

		RecordView
		{
			anchors.top: controlPanel.bottom
			anchors.right: parent.right
			anchors.left: parent.left
			anchors.bottom: parent.bottom
		}
}
