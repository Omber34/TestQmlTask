//
// Created by Herman on 2/9/2024.
//

#include "RecordModel.h"

#include <QPainter>

#include <stdexcept>


QVariant RecordModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return {};

  const auto& record = records[records.size() - index.row() - 1];

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
  return records.size();
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
  auto iter = std::find_if(records.begin(), records.end(), [&id] (const Record& record) { return record.hash == id; });
  if (iter == records.end())
    throw std::logic_error("cant find a requested pixmap.");

  auto& pixmap = iter->image;
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
    const auto rect = pixmap.rect();
    painter.scale(rect.width() / width, rect.height() / height);
  }

  return pixmap;
}

RecordModel::RecordModel(QObject *parent)
  : QAbstractListModel(parent)
  , QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}

void RecordModel::addNewRecord(const Record& record)
{
  beginInsertRows(QModelIndex(), 0, 0);
  records.push_back(record);
  endInsertRows();
}

