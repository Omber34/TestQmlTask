import QtQuick 2.12
import QtGraphicalEffects 1.0


Item {
    id: root

    property alias imageSource: image.source
    property alias hashText: hash.text
    property alias similarToPrevText: similarToPrev.text
    readonly property int cellHeight: Constants.previewImageHeight + hash.height

    Column
    {
	      Text
	      {
	        anchors.horizontalCenter: parent.horizontalCenter
	        id: similarToPrev
	      }

	      Text
	      {
	        anchors.horizontalCenter: parent.horizontalCenter
	        id: hash
	      }

	      Rectangle {
	          color: 'transparent'
	          height: Constants.previewImageHeight
	          width: Constants.previewImageWidth

	          Image {
                id: image
                anchors.fill: parent
                sourceSize.height: height
                sourceSize.width: width
            }
        }
    }
}
