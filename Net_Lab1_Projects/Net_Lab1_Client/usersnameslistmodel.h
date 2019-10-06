#ifndef USERSNAMESLISTMODEL_H
#define USERSNAMESLISTMODEL_H
#include <QStringListModel>

class UsersNamesListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    UsersNamesListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    //bool insertRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    QStringList usersNamesList;
};


#endif // USERSNAMESLISTMODEL_H
