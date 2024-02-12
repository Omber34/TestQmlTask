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

  model = QSharedPointer<QSqlTableModel>::create(this, db);

  model->setTable(tableName);
  model->setEditStrategy(QSqlTableModel::OnManualSubmit);
  model->sort(0, Qt::SortOrder::DescendingOrder);

  model->setHeaderData(0, Qt::Horizontal, "shot_id");
  model->setHeaderData(1, Qt::Horizontal, "hash");
  model->setHeaderData(2, Qt::Horizontal, "similarity");
  model->setHeaderData(3, Qt::Horizontal, "image_data");


  auto *worker = new DatabaseWorker(model);
  worker->moveToThread(&workerThread);
  connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
  connect(this, &DatabaseManager::storeRecord, worker, &DatabaseWorker::storeRecord);
  connect(this, &DatabaseManager::startLoadRecords, worker, &DatabaseWorker::loadByRecord);
  connect(worker, &DatabaseWorker::recordLoaded, this, &DatabaseManager::recordLoaded);
  workerThread.start();
}

DatabaseManager::~DatabaseManager()
{
  workerThread.quit();
  workerThread.wait();
}

DatabaseWorker::DatabaseWorker(QSharedPointer<QSqlTableModel> model)
: model(model)
{

}

void DatabaseWorker::loadByRecord()
{
  model->select();
  const auto size = model->rowCount();
  for (int i = 0; i < size; ++i)
  {
    Record newRecord;
    newRecord.hash = model->record(i).value("hash").toString();
    newRecord.similarity = model->record(i).value("similarity").toFloat();

    auto imageData = model->record(i).value("image_data").toByteArray();
    QPixmap pixmap;
    pixmap.loadFromData(imageData);
    ImageStorage::getInstance().putImage(newRecord.hash, pixmap);

    emit recordLoaded(newRecord);
  }
}

void DatabaseWorker::storeRecord(const Record &record)
{
  auto db = QSqlDatabase::database(driverName);
  db.transaction();

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

  if (!model->submitAll())
  {
    qDebug() << "Error inserting record into table: \n" << model->lastError();
    db.rollback();
  }

  db.commit();
}
