#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <QObject>

class TransactionManager : public QObject
{
    Q_OBJECT
private:
    explicit TransactionManager(QObject *parent = nullptr);

signals:
};

#endif // TRANSACTIONMANAGER_H
