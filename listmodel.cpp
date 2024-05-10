#include "listmodel.h"
#include "dbmanager.h"

ListModel::ListModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    this->updateModel();
}

// The method for obtaining data from the model
QVariant ListModel::data(const QModelIndex & index, int role) const {

    // Define the column number, on the role of number
    int columnId = role - Qt::UserRole - 1;
    // Create the index using a column ID
    QModelIndex modelIndex = this->index(index.row(), columnId);

    //return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QHash<int, QByteArray> ListModel::roleNames() const {

    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[TitleRole] = "Title";
    roles[AuthorRole] = "Author";
    roles[GenreRole] = "Genre";
    roles[PriceRole] = "Price";
    roles[AmountRole] = "Amount";
    return roles;
}

// The method updates the tables in the data model representation
void ListModel::updateModel()
{
    // The update is performed SQL-queries to the database
    this->setQuery("SELECT id, Title, Author, Genre, Price, Amount FROM " TABLE);
    /*
    this->setQuery("SELECT id, " TABLE_TITLE ", " TABLE_AUTHOR ", " TABLE_GENRE
                   ", " TABLE_YEAR ", " TABLE_PRICE ", " TABLE_AMOUNT
                   " FROM " TABLE);
     */
}

// Getting the id of the row in the data view model
int ListModel::getId(int row)
{
    return this->data(this->index(row, 0), IdRole).toInt();
}

bool ListModel::search(const QString &str)
{
    /*
    if (!str.isEmpty()){
        filter = true;
        filterString = str;
    }
    else filter = false;
    */

    QSqlQuery query;
    query.prepare("SELECT * FROM Books "
                  "Where id LIKE ? or Title LIKE ? or "
                  "Author LIKE ? or Genre LIKE ? or "
                  "Price LIKE ? or Amount LIKE ? ");

    query.addBindValue(QString("%1%").arg(str));
    query.addBindValue(QString("%2%").arg(str));
    query.addBindValue(QString("%3%").arg(str));
    query.addBindValue(QString("%4%").arg(str));
    query.addBindValue(QString("%5%").arg(str));
    query.addBindValue(QString("%6%").arg(str));

    if(!query.exec()){
        qDebug() << query.lastError().text();
        return false;
    }
    this->setQuery(query);
    return true;

}

