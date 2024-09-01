#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "communicator.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/ChatRoom/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    Communicator *obj = new Communicator() ;
    engine.rootContext()->setContextProperty("Communicator" , obj ) ;

    engine.load(url);

    return app.exec();
}
