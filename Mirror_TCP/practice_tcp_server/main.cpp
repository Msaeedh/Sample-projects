#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "reciever.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/practice_tcp_server/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);


    Reciever *Reciever = new class Reciever() ;
    engine.rootContext()->setContextProperty("Reciever" , Reciever ) ;

    engine.load(url);

    return app.exec();
}
