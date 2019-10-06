#include "usersnameslistmodel.h"

UsersNamesListModel::UsersNamesListModel(QObject *parent)
    :QAbstractListModel(parent)
{
    //usersNamesList = _usersNamesList;
}

int UsersNamesListModel::rowCount(const QModelIndex &) const
{
    return usersNamesList.size();
}

QVariant UsersNamesListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return usersNamesList.at(index.row());
    }
    return QVariant();
}


bool UsersNamesListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        if (!checkIndex(index))
            return false;
        //usersNamesList.push_back(value.toString());
        int row = index.row();
        usersNamesList.insert(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool UsersNamesListModel::removeRows(int row, int count, const QModelIndex &index)
{
    beginRemoveRows(index, row, row + count - 1);
    for (int i = row; i <= row + count - 1; ++i) {
        usersNamesList.removeAt(i);
    }
    endRemoveRows();
    return true;
}

bool UsersNamesListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for (int i = row; i <= row + count - 1; ++i) {
        usersNamesList.insert(i, "");
    }
    endInsertRows();
    return true;
}


