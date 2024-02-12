//
// Created by Herman on 2/12/2024.
//

#include "DatabaseManager.h"
#include "ImageStorage.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QBuffer>


namespace
{
  const QString tableName = "screenshots";
  const QString driverName = "QSQLITE";
}

DatabaseManager::DatabaseManager(QObject *parent)
: QObject(parent)
{
  QSqlDatabase db = QSqlDatabase::addDatabase(driverName);
  db.setDatabaseName(tableName + ".db");
  db.open();

  QSqlQuery query(db);
  query.exec("CREATE TABLE IF NOT EXISTS " + tableName + " ( "
             "shot_id INTEGER PRIMARY KEY AUTOINCREMENT,"
             "hash TEXT,"
             "similarity REAL, "
             "image_data BLOB "
             ")");

  model = std::make_unique<QSqlTableModel>(this, db);

  model->setTable(tableName);
  model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  model->setHeaderData(0, Qt::Horizontal, tr("shot_id"));
  model->setHeaderData(1, Qt::Horizontal, tr("hash"));
  model->setHeaderData(2, Qt::Horizontal, tr("similarity"));
  model->setHeaderData(3, Qt::Horizontal, tr("image_data"));
}

QList<Record> DatabaseManager::loadHistory()
{
  model->select();
  const auto size = model->rowCount();
  QList<Record> records;
  for (int i = 0; i < size; ++i)
  {
    Record newRecord;
    newRecord.hash = model->record(i).value("hash").toString();
    newRecord.similarity = model->record(i).value("similarity").toFloat();
    records.push_back(newRecord);

    auto imageData = model->record(i).value("image_data").toByteArray();
    QPixmap pixmap;
    pixmap.loadFromData(imageData);
    ImageStorage::getInstance().putImage(newRecord.hash, pixmap);
  }

  return records;
}

void DatabaseManager::storeHistory(const QList<Record> &records)
{
  auto db = QSqlDatabase::database(driverName);
  db.transaction();

  for (const auto& record: records)
  {
    QSqlRecord sqlRecord = model->record();

    sqlRecord.remove(sqlRecord.indexOf("shot_id"));
    sqlRecord.setValue("hash", record.hash);
    sqlRecord.setValue("similarity", record.similarity);

    const auto pixmap = ImageStorage::getInstance().getImage(record.hash);
    QByteArray pixmapToBlob;
    QBuffer buffer(&pixmapToBlob);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG");

    sqlRecord.setValue("image_data", pixmapToBlob);

    model->insertRecord(-1, sqlRecord);
  }

  if (!model->submitAll())
  {
    qDebug() << "Error inserting records into table: \n" << model->lastError();
    db.rollback();
  }

  db.commit();
}

