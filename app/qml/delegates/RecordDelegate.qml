import QtQuick 2.12
import QtQuick.Layouts 1.15


Item {
  id: root

  property alias imageSource: image.source
  property alias hashText: hash.text
  property alias similarToPrevText: similarToPrev.text

  ColumnLayout
  {
    anchors.fill: parent
    Text
    {
      Layout.alignment: Qt.AlignHCenter
      id: similarToPrev
    }

    Text
    {
      Layout.alignment: Qt.AlignHCenter
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
