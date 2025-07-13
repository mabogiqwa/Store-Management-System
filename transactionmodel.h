#ifndef TRANSACTIONMODEL_H
#define TRANSACTIONMODEL_H

#include <QAbstractItemModel>
#include <QObject>
#include "customer.h"
#include "transaction.h"

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
};

#endif // TRANSACTIONMODEL_H
