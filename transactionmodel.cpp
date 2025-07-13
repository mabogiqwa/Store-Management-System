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
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid()) {

        if (row < mCustomerNodes.size()) {
            return createIndex(row, column, nullptr);
        }
    } else {
        int customerIndex = parent.row();
        if (customerIndex < mCustomerNodes.size()) {
            const CustomerNode &node = mCustomerNodes[customerIndex];
            if (row < node.transactions.size()) {
                return createIndex(row, column, node.transactions[row]);
            }
        }
    }

    return QModelIndex();
}

QModelIndex TransactionModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    Transaction *transaction = static_cast<Transaction*>(child.internalPointer());

    if (transaction) {
        for (int i = 0; i < mCustomerNodes.size(); i++) {
            if (mCustomerNodes[i].transactions.contains(transaction)) {
                return createIndex(i, 0, nullptr);
            }
        }
    }

    return QModelIndex();
}

int TransactionModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return mCustomerNodes.size();
    } else {
        int customerIndex = parent.row();
        if (customerIndex < mCustomerNodes.size()) {
            return mCustomerNodes[customerIndex].transactions.size();
        }
    }

    return 0;
}

int TransactionModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 3;
}

QVariant TransactionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        Transaction *transaction =
    }
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
