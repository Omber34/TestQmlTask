//
// Created by Herman on 2/11/2024.
//

#include "ImageComparer.h"
#include "ImageStorage.h"

namespace
{
  float compareImages(const QPixmap& left, const QPixmap& right)
  {
    if (left.isNull() || right.isNull())
      return 0.0f;

    auto leftImage = left.toImage();
    auto rightImage = right.toImage();

    size_t differentPixels = 0;
    for (int x = 0; x < leftImage.width(); ++x)
      for (int y = 0; y < leftImage.height(); ++y)
        if (rightImage.pixel(x, y) != leftImage.pixel(x, y))
          ++differentPixels;


    const auto pixelCount = leftImage.width() * leftImage.width();
    return 100.0f - (static_cast<float>(differentPixels) / static_cast<float>(pixelCount) * 100.0f);
  }
}

void ComparerWorker::compareImages(const QString &prev, const QString &curr)
{
  auto& storage = ImageStorage::getInstance();
  float result = ::compareImages(storage.getImage(prev), storage.getImage(curr));

  emit resultReady(curr, result);
}

ImageComparer::ImageComparer()
{
  auto *worker = new ComparerWorker;
  worker->moveToThread(&workerThread);
  connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
  connect(this, &ImageComparer::startImageComprasion, worker, &ComparerWorker::compareImages);
  connect(worker, &ComparerWorker::resultReady, this, &ImageComparer::resultReady);
  workerThread.start();
}

ImageComparer::~ImageComparer()
{
  workerThread.quit();
  workerThread.wait();
}

