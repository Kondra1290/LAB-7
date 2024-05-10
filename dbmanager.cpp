#include "dbmanager.h"

DBManager::DBManager(QObject *parent)
    : QObject{parent}
{}

DBManager::~DBManager(){}

void DBManager::connectToDataBase()
{
    if(!QFile("C:\\Users\\shura\\Documents\\LAB-7\\" DATABASE_NAME).exists()){
        qDebug() << "Файла БД нет!";
    } else {
        this->openDataBase();
    }
}

bool DBManager::openDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("C:\\Users\\shura\\Documents\\LAB-7\\" DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

void DBManager::closeDataBase()
{
    db.close();
}

/*
bool DBManager::inserIntoTable(const QVariantList &data)
{
    QSqlQuery query;

    query.prepare("INSERT INTO Books(Title, Author, Genre, Pub_year, Price, Amount) VALUES (?, ?, ?, ?, ?, ?)");

    query.bindValue(0, data[0].toString());
    query.bindValue(1, data[1].toString());
    query.bindValue(2, data[2].toString());
    query.bindValue(3, data[3].toString());
    query.bindValue(4, data[4].toDouble());
    query.bindValue(5, data[5].toInt());

    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
*/
bool DBManager::inserIntoTable(const QString &title, const QString &author, const QString &genre,
                               const QString &price, const QString &amount)
{
    if(title.isEmpty() || author.isEmpty() || genre.isEmpty() || price.isEmpty() || amount.isEmpty()) return false;

    QSqlQuery query;

    query.prepare("INSERT INTO Books(Title, Author, Genre, Price, Amount) VALUES (?, ?, ?, ?, ?)");

    query.bindValue(0, title);
    query.bindValue(1, author);
    query.bindValue(2, genre);
    query.bindValue(3, price);
    query.bindValue(4, amount);

    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool DBManager::removeRecord(const int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM " TABLE " WHERE id= :ID ;");
    query.bindValue(":ID", id);

    if(!query.exec()){
        qDebug() << "error delete row " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool DBManager::updateRecord(const QString &id, const QString &title, const QString &author,
                             const QString &genre, const QString &price, const QString &amount)
{
    QSqlQuery query;

    query.prepare("INSERT INTO Books(Title, Author, Genre, Price, Amount) VALUES (?, ?, ?, ?, ?)");

    query.bindValue(0, title);
    query.bindValue(1, author);
    query.bindValue(2, genre);
    query.bindValue(3, price);
    query.bindValue(4, amount);

    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}
