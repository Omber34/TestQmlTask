//
// Created by Herman on 2/9/2024.
//

#pragma once

#include "RecordModel.h"

#include <QObject>
#include <QTimer>

class ScreenSaver : public QObject
{
  Q_OBJECT
  Q_PROPERTY(RecordModel* model MEMBER model WRITE setModel)

public:
  explicit ScreenSaver(QObject *parent = nullptr);

public slots:
  void start();
  void stop();
  void takeNewRecord();
  void setModel(RecordModel* newModel);

signals:
  void onNewRecord(const Record& record);

private:
  QTimer timer;
  RecordModel* model;
};
