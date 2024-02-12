//
// Created by Herman on 2/12/2024.
//

#pragma once
#include <QtSql/QSqlTableModel>
#include <QThread>
#include "Record.h"

class DatabaseWorker : public QObject
{
  Q_OBJECT
public:
  DatabaseWorker(QSharedPointer<QSqlTableModel> model);

public slots:
  void storeRecord(const Record& record);
  void loadByRecord();

signals:
  void recordLoaded(const Record& record);

private:
  QSharedPointer<QSqlTableModel> model;
};

class DatabaseManager : public QObject
{
  Q_OBJECT
public:
  explicit DatabaseManager(QObject* parent = nullptr);
  ~DatabaseManager();

signals:
  void storeRecord(const Record& record);
  void recordLoaded(const Record& record);
  void startLoadRecords();

private:
  QSharedPointer<QSqlTableModel> model;
  QThread workerThread;
};
