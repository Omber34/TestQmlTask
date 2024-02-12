pragma Singleton

import QtQml 2.15
import QtQuick 2.12

QtObject {
    readonly property int previewImageHeight: 180
    readonly property int previewImageWidth: 320

    readonly property int gridCellHeight: previewImageHeight + (20 * 2)

}
