#include "transactionmodel.h"

TransactionModel::TransactionModel(QObject *parent) : QAbstractItemModel(parent)
{
    buildCustomerNodes();
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
    } else if (!parent.parent().isValid()) {
        int customerIndex = parent.row();
        if (customerIndex < mCustomerNodes.size()) {
            const CustomerNode &node = mCustomerNodes[customerIndex];
            if (row < node.transactions.size()) {
                return createIndex(row, column, node.transactions[row]);
            }
        }
    } else {
        Transaction *transaction = static_cast<Transaction*>(parent.internalPointer());
        if (transaction) {
            const QList<PurchaseItem> &items = transaction->getItems();
            if (row < items.size()) {
                void *itemPtr = reinterpret_cast<void*>(
                    reinterpret_cast<uintptr_t>(transaction) + row + 1
                );
                return createIndex(row, column, itemPtr);
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
        Transaction *transaction = static_cast<Transaction*>(index.internalPointer());

        if (!transaction) {
            int customerIndex = index.row();
            if (customerIndex < mCustomerNodes.size()) {
                const CustomerNode &node = mCustomerNodes[customerIndex];
                if (index.column() == 0) {
                    return node.customer->getName();
                }
            }
        } else {
            switch(index.column()) {
                case 0:
                    return transaction->getDateTime().toString("yyyy-MM-dd hh:mm:ss");
                case 1: {
                    QStringList itemNames;
                    for (const PurchaseItem &item : transaction->getItems()) {
                        itemNames << item.item->getName();
                    }
                    return itemNames.join(", ");
                }
                case 2: {
                    QStringList quantities;
                    for (const PurchaseItem &item : transaction->getItems()) {
                        quantities << QString::number(item.quantity);
                    }
                    return quantities.join(", ");
                }
            }
        }
    }

    return QVariant();
}

QVariant TransactionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case 0: return "Customer/Date";
            case 1: return "Items";
            case 2: return "Quantities";
        }
    }

    return QVariant();
}

void TransactionModel::refreshModel()
{
    beginResetModel();
    buildCustomerNodes();
    endResetModel();
}

void TransactionModel::buildCustomerNodes()
{
    mCustomerNodes.clear();

    TransactionManager *transactionManager = TransactionManager::getInstance();
    QList<Transaction*> allTransactions = transactionManager->getTransactions();

    QHash<Customer*, QList<Transaction*>> customerTransactions;
    for (Transaction *transaction : allTransactions) {
        customerTransactions[transaction->getCustomer()].append(transaction);
    }

    for (auto it = customerTransactions.begin(); it != customerTransactions.end(); ++it) {
        CustomerNode node;
        node.customer = it.key();
        node.transactions = it.value();
        mCustomerNodes.append(node);
    }
}
