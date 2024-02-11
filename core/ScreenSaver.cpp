//
// Created by Herman on 2/9/2024.
//

#include <QGuiApplication>
#include <QBuffer>
#include <QScreen>
#include <QCryptographicHash>
#include <stdexcept>
#include "ScreenSaver.h"

namespace
{
  QByteArray pixmapToByteArray(const QPixmap& pixmap)
  {
    QByteArray pixmapToHash;
    QBuffer buffer(&pixmapToHash);

    buffer.open(QIODevice::WriteOnly);
    auto grayPixmap = pixmap.toImage().convertToFormat(QImage::Format_Grayscale8);
    grayPixmap.save(&buffer, "PNG");

    return pixmapToHash;
  }

  Record createNewRecord()
  {
    auto* screen = QGuiApplication::primaryScreen();

    auto screenshot = screen->grabWindow(0);

    QByteArray pixmapHash = pixmapToByteArray(screenshot);

    QString hash = QString(QCryptographicHash::hash(pixmapHash, QCryptographicHash::Md5).toHex());
    return Record{screenshot,  0.0f, hash};
  }

  float compareImages(const QPixmap& left, const QPixmap& right)
  {
    if (left.isNull() || right.isNull())
      return 0.0f;

    auto leftHash = pixmapToByteArray(left);
    auto rightHash = pixmapToByteArray(right);

    QByteArray diff;
    diff.reserve(std::min(leftHash.size(), rightHash.size()));

    size_t nonZeroCount = 0;
    for (int i = 0; i < diff.capacity(); ++i)
    {
      const auto value = static_cast<char>(std::abs(static_cast<int>(leftHash[i] - rightHash[i])));
      diff.push_back(value);
      if (value != 0) ++nonZeroCount;
    }

    return static_cast<float>(nonZeroCount) / static_cast<float>(diff.size()) * 100.0f;
  }
}

ScreenSaver::ScreenSaver(const RecordModel &model)
{
  connect(&timer, &QTimer::timeout, this, &ScreenSaver::takeNewRecord);
  connect(this, &ScreenSaver::onNewRecord, &model, &RecordModel::addNewRecord);
}

void ScreenSaver::start()
{
  takeNewRecord();
  timer.start(1000);
}

void ScreenSaver::stop()
{
  timer.stop();
}

void ScreenSaver::takeNewRecord()
{
  auto newRecord = createNewRecord();
  newRecord.similarToPrev = compareImages(newRecord.image, previousShot);
  previousShot = newRecord.image;
  emit onNewRecord(newRecord);
}

