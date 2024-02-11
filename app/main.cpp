#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "RecordModel.h"
#include "ScreenSaver.h"


int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    auto* model= new RecordModel;
    ScreenSaver saver(*model);
    saver.start();

    QQmlApplicationEngine engine;
    engine.addImportPath ("qrc:/");
    engine.addImageProvider(ScreenshotPrefix, model);

    qmlRegisterSingletonType(QUrl("qrc:/Constants.qml"),
      "Constants", 1, 0, "Constants");
    qmlRegisterSingletonInstance("models", 1, 0, "RecordModel", model);
    qmlRegisterSingletonInstance("models", 1, 0, "ScreenSaver", &saver);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
