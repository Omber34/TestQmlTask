#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "RecordModel.h"
#include "ScreenSaver.h"
#include "ImageStorage.h"


int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);
  const QUrl url(QStringLiteral("qrc:/main.qml"));

  QQmlApplicationEngine engine;

  engine.addImportPath ("qrc:/");
  engine.addImageProvider(ScreenshotPrefix, &ImageStorage::getInstance());

  qmlRegisterSingletonType(QUrl("qrc:/Constants.qml"),
    "Constants", 1, 0, "Constants");
  qmlRegisterType<RecordModel>("models", 1, 0, "RecordModel");
  qmlRegisterType<ScreenSaver>("models", 1, 0, "ScreenSaver");

  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
              if (!obj && url == objUrl)
                  QCoreApplication::exit(-1);
          }, Qt::QueuedConnection);

  engine.load(url);

  return app.exec();
}
