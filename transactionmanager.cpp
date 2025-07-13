#include "transactionmanager.h"

TransactionManager* TransactionManager::sInstance = nullptr;

TransactionManager::TransactionManager(QObject *parent)
    : QObject{parent}
{}

TransactionManager* TransactionManager::getInstance()
{
    if (!sInstance) {
        sInstance = new TransactionManager();
    }
    return sInstance;
}

void TransactionManager::addTransaction(Transaction *transaction) {
    mTransactions.append(transaction);
    emit transactionAdded(transaction);
}

QList<Transaction*> TransactionManager::getTransactions() const
{
    return mTransactions;
}

QList<Transaction*> TransactionManager::getTransactionsForCustomer(Customer *customer) const
{
    QList<Transaction*> customerTransactions;
    for (Transaction *transaction : mTransactions) {
        if (transaction->getCustomer() == customer) {
            customerTransactions.append(transaction);
        }
    }
    return customerTransactions;
}

TransactionManager::~TransactionManager() {
    qDeleteAll(mTransactions);
    mTransactions.clear();
}
