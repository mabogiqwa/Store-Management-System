#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDateTime>
#include <QList>

class Customer;
class Item;

struct PurchaseItem {
    Item *item;
    int quantity;

    PurchaseItem(Item *i, int q) : item(i), quantity(q)
    {}
};

class Transaction
{
public:
    explicit Transaction(Customer *customer, const QDateTime &dateTime);
    ~Transaction();


};

#endif // TRANSACTION_H
