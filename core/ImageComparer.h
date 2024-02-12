//
// Created by Herman on 2/11/2024.
//

#pragma once
#include <QObject>
#include <QThread>

class Worker : public QObject
{
  Q_OBJECT

public slots:

  void doWork(const QString &prev, const QString &curr);

signals:

  void resultReady(const QString &id, const float &result);

};

class ImageComparer : public QObject
{
  Q_OBJECT
public:
  ImageComparer();

  ~ImageComparer() override;

signals:
    void resultReady(const QString &id, float similarityToPrev);
    void operate(const QString &, const QString &);

private:
  QThread workerThread;
};