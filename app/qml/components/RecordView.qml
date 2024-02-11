import QtQuick 2.12
import models 1.0

GridView
{
	id: grid
  cellWidth: Constants.previewImageWidth
  cellHeight: Constants.gridCellHeight

  model: RecordModel
  delegate: RecordDelegate
  {
    width: grid.cellWidth; height: grid.cellHeight
    imageSource: image
    hashText: hash
    similarToPrevText: similarToPrev
  }
}