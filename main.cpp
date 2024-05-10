#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "dbmanager.h"
#include "listmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<ListModel>("ListModel", 0, 1, "ListModel");


    DBManager database;
    database.connectToDataBase();

    ListModel model;
    engine.rootContext()->setContextProperty("myModel", &model);

    engine.rootContext()->setContextProperty("sqlitedatabase", &database);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("LAB-7", "Main");

    return app.exec();
}
