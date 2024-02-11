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
public:
  explicit ScreenSaver(const RecordModel& model);

public slots:
  void start();
  void stop();
  void takeNewRecord();

signals:
  void onNewRecord(const Record& record);

private:
  QTimer timer;
  QPixmap previousShot;

};
