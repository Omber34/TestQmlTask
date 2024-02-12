//
// Created by Herman on 2/9/2024.
//

#include <QGuiApplication>
#include <QBuffer>
#include <QScreen>
#include "ScreenSaver.h"
#include "ImageStorage.h"

namespace
{
  QPixmap takeScreenshot()
  {
    auto* screen = QGuiApplication::primaryScreen();

    auto screenshot = screen->grabWindow(0);

    return screenshot
//    .scaled(PreviewImageSize)
    ;
  }

  Record createNewRecord(const QPixmap& pixmap)
  {
    QString hash = QString::number(pixmap.cacheKey());

    return Record{0.0, hash};
  }
}

ScreenSaver::ScreenSaver(QObject *parent)
: QObject(parent)
{
}

void ScreenSaver::start()
{
  takeNewRecord();
  timer.start(1000 * 60);
}

void ScreenSaver::stop()
{
  timer.stop();
}

void ScreenSaver::takeNewRecord()
{
  const auto newShot = takeScreenshot();
  auto newRecord = createNewRecord(newShot);
  ImageStorage::getInstance().putImage(newRecord.hash, newShot);
  emit onNewRecord(newRecord);
}

void ScreenSaver::setModel(RecordModel* newModel)
{
  if (!newModel)
    return;

  model = newModel;
  connect(&timer, &QTimer::timeout, this, &ScreenSaver::takeNewRecord);
  connect(this, &ScreenSaver::onNewRecord, model, &RecordModel::addNewRecord);
}


