//
// Created by Herman on 2/9/2024.
//

#pragma once

#include <QAbstractListModel>
#include "Record.h"
#include "ImageComparer.h"
#include "DatabaseManager.h"

const auto ScreenshotPrefix = "shots";

class RecordModel : public QAbstractListModel
{
  Q_OBJECT
  enum
  {
    HashRole = Qt::UserRole + 1,
    ImageRole,
    SimilarToPrevRole
  };

public:
  explicit RecordModel(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

  ~RecordModel() override;

public slots:

  void addNewRecord(const Record& record);
  void processCompareResult(const QString& id, float similarity);
  void onRecordLoaded(const Record &newRecord);

private:
  QList<Record> records;
  ImageComparer comparer;
  DatabaseManager databaseManager;
};
