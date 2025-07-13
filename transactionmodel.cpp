#include "transactionmodel.h"

TransactionModel::TransactionModel(QObject *parent) : QAbstractItemModel(parent)
{
    //buildCustomerNodes();
}

TransactionModel::~TransactionModel()
{

}

QModelIndex TransactionModel::index(int row, int column, const QModelIndex &parent) const
{

}

QModelIndex TransactionModel::parent(const QModelIndex &child) const
{

}

int TransactionModel::rowCount(const QModelIndex &parent) const
{

}

int TransactionModel::columnCount(const QModelIndex &parent) const
{

}

QVariant TransactionModel::data(const QModelIndex &index, int role) const
{

}

QVariant TransactionModel::headerData(int section, Qt::Orientation orientation, int role) const
{

}

void TransactionModel::refreshModel()
{

}

void TransactionModel::buildCustomerNodes()
{

}
