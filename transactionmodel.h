#ifndef TRANSACTIONMODEL_H
#define TRANSACTIONMODEL_H

#include <QAbstractItemModel>
#include <QObject>
#include <QStringList>
#include <QVariant>
#include "customer.h"
#include "transaction.h"
#include "transactionmanager.h"
#include "item.h"

struct ItemIdentifier {
    Transaction *transaction;
    int itemIndex;

    ItemIdentifier(Transaction *t, int idx) : transaction(t), itemIndex(idx) {}
};

class TransactionModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit TransactionModel(QObject *parent = nullptr);
    ~TransactionModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

public slots:
    void refreshModel();

private:
    struct CustomerNode {
        Customer *customer;
        QList<Transaction*> transactions;
    };

    QList<CustomerNode> mCustomerNodes;
    void buildCustomerNodes();
    mutable QList<ItemIdentifier*> mItemIdentifiers;
};

#endif // TRANSACTIONMODEL_H
