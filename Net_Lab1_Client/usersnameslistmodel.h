#ifndef USERSNAMESLISTMODEL_H
#define USERSNAMESLISTMODEL_H
#include <QStringListModel>

class UsersNamesListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    UsersNamesListModel(const QString &usersNamesList, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool insertRow(int row, const QModelIndex &parent);

private:
    QStringList usersNamesList;
};


#endif // USERSNAMESLISTMODEL_H
