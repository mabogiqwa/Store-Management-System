#include "transactionmodel.h"

TransactionModel::TransactionModel(QObject *parent) : QAbstractItemModel(parent)
{
    buildCustomerNodes();
}

TransactionModel::~TransactionModel()
{
    qDeleteAll(mItemIdentifiers);
    mItemIdentifiers.clear();
}

QModelIndex TransactionModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid()) {
        // Top level - customers
        if (row < mCustomerNodes.size()) {
            return createIndex(row, column, nullptr);
        }
    } else if (!parent.parent().isValid()) {
        // Second level - transactions under customers
        int customerIndex = parent.row();
        if (customerIndex < mCustomerNodes.size()) {
            const CustomerNode &node = mCustomerNodes[customerIndex];
            if (row < node.transactions.size()) {
                return createIndex(row, column, node.transactions[row]);
            }
        }
    } else {
        // Third level - items under transactions
        Transaction *transaction = static_cast<Transaction*>(parent.internalPointer());
        if (transaction) {
            const QList<PurchaseItem> &items = transaction->getItems();
            if (row < items.size()) {
                // Create a unique identifier for this item
                ItemIdentifier *itemId = new ItemIdentifier(transaction, row);
                mItemIdentifiers.append(itemId);
                return createIndex(row, column, itemId);
            }
        }
    }

    return QModelIndex();
}

QModelIndex TransactionModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    void *ptr = child.internalPointer();

    if (!ptr) {
        // This is a customer node (top level), so no parent
        return QModelIndex();
    }

    // Check if this is a transaction pointer
    for (int i = 0; i < mCustomerNodes.size(); i++) {
        const CustomerNode &node = mCustomerNodes[i];
        for (int j = 0; j < node.transactions.size(); j++) {
            if (ptr == node.transactions[j]) {
                // This is a transaction, parent is customer
                return createIndex(i, 0, nullptr);
            }
        }
    }

    // Check if this is an item identifier
    ItemIdentifier *itemId = static_cast<ItemIdentifier*>(ptr);
    for (int i = 0; i < mCustomerNodes.size(); i++) {
        const CustomerNode &node = mCustomerNodes[i];
        for (int j = 0; j < node.transactions.size(); j++) {
            if (itemId->transaction == node.transactions[j]) {
                // This is an item, parent is transaction
                return createIndex(j, 0, itemId->transaction);
            }
        }
    }

    return QModelIndex();
}

int TransactionModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        // Top level - return number of customers
        return mCustomerNodes.size();
    } else if (!parent.parent().isValid()) {
        // Second level - return number of transactions for this customer
        int customerIndex = parent.row();
        if (customerIndex < mCustomerNodes.size()) {
            return mCustomerNodes[customerIndex].transactions.size();
        }
    } else {
        // Third level - return number of items for this transaction
        Transaction *transaction = static_cast<Transaction*>(parent.internalPointer());
        if (transaction) {
            return transaction->getItems().size();
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
        void *ptr = index.internalPointer();

        if (!ptr) {
            // This is a customer node
            int customerIndex = index.row();
            if (customerIndex < mCustomerNodes.size()) {
                const CustomerNode &node = mCustomerNodes[customerIndex];
                if (index.column() == 0) {
                    return node.customer->getName();
                }
            }
        } else {
            // Check if this is a transaction pointer
            bool isTransaction = false;
            for (int i = 0; i < mCustomerNodes.size() && !isTransaction; i++) {
                const CustomerNode &node = mCustomerNodes[i];
                for (int j = 0; j < node.transactions.size(); j++) {
                    if (ptr == node.transactions[j]) {
                        isTransaction = true;
                        Transaction *transaction = node.transactions[j];
                        switch(index.column()) {
                        case 0:
                            return transaction->getDateTime().toString("yyyy/MM/dd hh:mm");
                        case 1:
                            return QString(); // Empty for transaction row
                        case 2:
                            return QString(); // Empty for transaction row
                        }
                        break;
                    }
                }
            }

            if (!isTransaction) {
                // This must be an item identifier
                ItemIdentifier *itemId = static_cast<ItemIdentifier*>(ptr);
                if (itemId && itemId->transaction) {
                    const QList<PurchaseItem> &items = itemId->transaction->getItems();
                    if (itemId->itemIndex < items.size()) {
                        const PurchaseItem &item = items[itemId->itemIndex];
                        switch(index.column()) {
                        case 0:
                            return item.item->getName();
                        case 1:
                            return item.item->getType() == Itemtype::Book ? "B" : "M";
                        case 2:
                            return item.quantity;
                        }
                    }
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
            case 0: return "Transaction";
            case 1: return "Type";
            case 2: return "Quantity";
        }
    }

    return QVariant();
}

void TransactionModel::refreshModel()
{
    beginResetModel();

    // Clean up old item identifiers
    qDeleteAll(mItemIdentifiers);
    mItemIdentifiers.clear();

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
