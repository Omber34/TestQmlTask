import QtQuick 2.12
import models 1.0


Item
{
	GridView
	{
    cellWidth: Constants.previewImageWidth
    cellHeight: Constants.gridCellHeight

		id: grid
    anchors.fill: parent

    model: RecordModel
    delegate: RecordDelegate
    {
      width: grid.cellWidth
      height: grid.cellHeight

      imageSource: image
      hashText: hash
      similarToPrevText: similarToPrev
    }
	}
}
