#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <QObject>
#include "transaction.h"
#include "customer.h"

class TransactionManager : public QObject
{
    Q_OBJECT
public:
    static TransactionManager* getInstance();
    void addTransaction(Transaction *transaction);
    QList<Transaction*> getTransactions() const;
    QList<Transaction*> getTransactionsForCustomer(Customer *customer) const;

signals:
    void transactionAdded(Transaction *transaction);

private:
    explicit TransactionManager(QObject *parent = nullptr);
    ~TransactionManager();

    static TransactionManager *sInstance;
    QList<Transaction*> mTransactions;
};

#endif // TRANSACTIONMANAGER_H
