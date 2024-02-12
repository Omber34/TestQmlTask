//
// Created by Herman on 2/11/2024.
//

#include "ImageComparer.h"
#include "ImageStorage.h"

namespace
{
  float compareImages(const QPixmap& left, const QPixmap& right)
  {
    const auto start = std::chrono::system_clock::now();
    if (left.isNull() || right.isNull())
      return 0.0f;

    auto leftImage = left.toImage();
    auto rightImage = right.toImage();

    size_t differentPixels = 0;
    for (int x = 0; x < leftImage.width(); ++x)
      for (int y = 0; y < leftImage.height(); ++y)
        if (rightImage.pixel(x, y) != leftImage.pixel(x, y))
          ++differentPixels;

    const auto end = std::chrono::system_clock::now();
    const std::chrono::milliseconds dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    qDebug() << "compareImages spent: " << dur.count() << "ms.";

    const auto pixelCount = leftImage.width() * leftImage.width();
    return 100.0f - (static_cast<float>(differentPixels) / static_cast<float>(pixelCount) * 100.0f);
  }
}


void Worker::doWork(const QString &prev, const QString &curr)
{
  auto& storage = ImageStorage::getInstance();
  float result = compareImages(storage.getImage(prev), storage.getImage(curr));

  emit resultReady(curr, result);
}

ImageComparer::ImageComparer()
{
  auto *worker = new Worker;
  worker->moveToThread(&workerThread);
  connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
  connect(this, &ImageComparer::operate, worker, &Worker::doWork, Qt::QueuedConnection);
  connect(worker, &Worker::resultReady, this, &ImageComparer::resultReady, Qt::QueuedConnection);
  workerThread.start();
}

ImageComparer::~ImageComparer()
{
  workerThread.quit();
  workerThread.wait();
}

