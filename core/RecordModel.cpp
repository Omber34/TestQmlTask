//
// Created by Herman on 2/9/2024.
//

#include "RecordModel.h"

#include <QScreen>
#include <QGuiApplication>
#include <QCryptographicHash>
#include <QBuffer>
#include <QPainter>

namespace
{
  Record createNewRecord()
  {
    auto* screen = QGuiApplication::primaryScreen();

    auto screenshot = screen->grabWindow(0);

    QByteArray pixmapToHash;
    QBuffer buffer(&pixmapToHash);

    buffer.open(QIODevice::WriteOnly);
    screenshot.save(&buffer, "PNG");

    QString hash = QString(QCryptographicHash::hash(pixmapToHash, QCryptographicHash::Md5).toHex());
    return Record{screenshot, 0.0, hash};
  }
}

QVariant RecordModel::data(const QModelIndex &index, int role) const
{
  switch (role)
  {
    case HashRole:
      return QVariant::fromValue(record.hash);
    case SimilarToPrevRole:
      return QVariant::fromValue(record.similarToPrev);
    case ImageRole:{
      const QString imagePathPattern = "image://%1/%2";
      return QVariant::fromValue(imagePathPattern.arg(ScreenshotPrefix).arg(record.hash));
    }
    default:
      return {};
  }
}

int RecordModel::rowCount(const QModelIndex &parent) const
{
  return 15;
}

QHash<int, QByteArray> RecordModel::roleNames() const
{
  QHash<int, QByteArray> result{
    {HashRole,  "hash"},
    {ImageRole, "image"},
    {SimilarToPrevRole, "similarToPrev"}
  } ;

  return result;
}

QPixmap RecordModel::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
  auto& pixmap = record.image;
  int width = 320;
  int height = 180;

  if (size)
    *size = QSize(width, height);
  QPainter painter(&pixmap);


  if (requestedSize.isValid())
  {
    painter.scale(requestedSize.width() / width, requestedSize.height() / height);
  }
  else
  {
    const auto rect = record.image.rect();
    painter.scale(rect.width() / width, rect.height() / height);
  }

  return pixmap;
}

RecordModel::RecordModel(QObject *parent)
  : QAbstractListModel(parent)
  , QQuickImageProvider(QQuickImageProvider::Pixmap)
  , record(createNewRecord())
{}

