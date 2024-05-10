#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

#define DATABASE_HOSTNAME   "NameDataBase"
#define DATABASE_NAME       "lab7_bd.db"

#define TABLE                   "Books"
#define TABLE_TITLE             "Title"
#define TABLE_GENRE             "Genre"
#define TABLE_AUTHOR            "Author"
#define TABLE_PRICE             "Price"
#define TABLE_AMOUNT            "Amount"

class DBManager : public QObject
{
    Q_OBJECT
public:
    explicit DBManager(QObject *parent = nullptr);
    ~DBManager();
    void connectToDataBase();

signals:

private:
    QSqlDatabase  db;

    bool openDataBase();
    void closeDataBase();
public slots:
    //bool inserIntoTable(const QVariantList &data);      // Adding entries to the table
    bool removeRecord(const int id);
    bool inserIntoTable(const QString &title, const QString &author, const QString &genre,
                        const QString &price, const QString &amount);
    bool updateRecord(const QString &id, const QString &title, const QString &author,
                      const QString &genre, const QString &price, const QString &amount);
};

#endif // DBMANAGER_H
