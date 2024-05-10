#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QSqlDatabase>
#include <QObject>
#include <QSql>
#include <QDebug>
#include <QSqlQueryModel>

class ListModel : public QSqlQueryModel
{
    Q_OBJECT
private:
    bool filter = false;
    QString filterString;
public:
    /* We list all the roles that will be used in the TableView.
     * As you can see, they have to be in the memory above the parameter Qt::UserRole.
     * Due to the fact that the information below this address is not for customizations
     * */
    enum Roles {
        IdRole = Qt::UserRole + 1,
        TitleRole,
        GenreRole,
        AuthorRole,
        PriceRole,
        AmountRole
    };

    explicit ListModel(QObject *parent = 0);

    // Override the method that will return the data
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

protected:
    /* hashed table of roles for speakers.
     * The method used in the wilds of the base class QAbstractItemModel,
     * from which inherits the class QSqlQueryModel
     * */
    QHash<int, QByteArray> roleNames() const override;

signals:

public slots:
    bool search(const QString &str);
    void updateModel();
    int getId(int row);
};

#endif // LISTMODEL_H
