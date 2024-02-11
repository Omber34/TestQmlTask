//
// Created by Herman on 2/9/2024.
//

#pragma once

#include <QAbstractListModel>
#include <QQuickImageProvider>
#include "Record.h"

const auto ScreenshotPrefix = "shots";

class RecordModel : public QAbstractListModel, public QQuickImageProvider
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

  QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;

public slots:

  void addNewRecord(const Record& record);

private:
  QList<Record> records;
};
