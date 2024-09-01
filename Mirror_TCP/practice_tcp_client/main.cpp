#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "sender.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Sender *Sender = new class Sender() ;
    engine.rootContext()->setContextProperty("Sender" , Sender ) ;

    const QUrl url(QStringLiteral("qrc:/practice_tcp_client/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);


    return app.exec();
}
