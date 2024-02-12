//
// Created by Herman on 2/9/2024.
//

#include "RecordModel.h"
#include "DatabaseManager.h"

#include <algorithm>

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
      return QVariant::fromValue(QString::number(record.similarity).left(6));
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
  QHash<int, QByteArray> result {
    {HashRole,  "hash"},
    {ImageRole, "image"},
    {SimilarToPrevRole, "similarToPrev"}
  };

  return result;
}

RecordModel::RecordModel(QObject *parent)
  : QAbstractListModel(parent)
  , databaseManager(this)
{
  connect(&comparer, &ImageComparer::resultReady, this, &RecordModel::processCompareResult, Qt::QueuedConnection);
  records = databaseManager.loadHistory();
}

void RecordModel::addNewRecord(const Record& record)
{
  if (!records.empty())
  {
    emit comparer.operate(records.back().hash, record.hash);
  }

  beginInsertRows(QModelIndex(), 0, 0);
  records.push_back(record);
  endInsertRows();
}

void RecordModel::processCompareResult(const QString& id, float similarity)
{
  const auto iter = std::find_if(records.begin(), records.end(), [&id] (const Record& record) { return record.hash == id; });
  if (iter == records.end())
    return;

  (*iter).similarity = similarity;

  emit dataChanged(createIndex(0, 0), createIndex(records.size() - 1, 0), {SimilarToPrevRole} );
}

RecordModel::~RecordModel()
{
  databaseManager.storeHistory(records);
}

