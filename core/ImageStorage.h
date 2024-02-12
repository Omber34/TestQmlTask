//
// Created by Herman on 2/11/2024.
//

#pragma once
#include <QObject>
#include <QMap>
#include <QQuickImageProvider>

const auto PreviewImageSize = QSize(320, 180);

class ImageStorage : public QObject, public QQuickImageProvider
{
  Q_OBJECT

public:

  void putImage(const QString& id, const QPixmap& image);
  QPixmap& getImage(const QString& id);

  QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;

  static ImageStorage& getInstance();

private:

  explicit ImageStorage(QObject* parent = nullptr);

  QMap<QString, QPixmap> pictures;
};
