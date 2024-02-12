//
// Created by Herman on 2/11/2024.
//

#include "ImageStorage.h"
#include <QPixmap>
#include <QPainter>

#include <stdexcept>

QPixmap ImageStorage::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
  auto& pixmap = getImage(id);
  auto width = PreviewImageSize.width();
  auto height = PreviewImageSize.height();

  if (size)
    *size = QSize(width, height);

  QPainter painter(&pixmap);
  if (requestedSize.isValid())
  {
    painter.scale(requestedSize.width() / width, requestedSize.height() / height);
  }
  else
  {
    const auto rect = pixmap.rect();
    painter.scale(rect.width() / width, rect.height() / height);
  }
  return pixmap;
}

ImageStorage::ImageStorage(QObject *parent)
  : QObject(parent)
  , QQuickImageProvider(QQuickImageProvider::Pixmap)
{

}

void ImageStorage::putImage(const QString &id, const QPixmap &image)
{
  pictures.insert(id, image);
}

QPixmap &ImageStorage::getImage(const QString &id)
{
  if (!pictures.contains(id))
    throw std::logic_error("cant find picture.");

  return pictures[id];
}

ImageStorage &ImageStorage::getInstance()
{
  static auto* imageStorage = new ImageStorage;
  return *imageStorage;
}
