//
// Created by Herman on 2/12/2024.
//

#pragma once
#include <QtSql/QSqlTableModel>
#include <QPixmap>
#include "Record.h"


class DatabaseManager : public QObject
{
  Q_OBJECT
public:
  explicit DatabaseManager(QObject* parent = nullptr);

  QList<Record> loadHistory();
  void storeHistory(const QList<Record>& records);

private:
  std::unique_ptr<QSqlTableModel> model;

};
