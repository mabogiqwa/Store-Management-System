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

    Customer* getCustomer() const;
    QDateTime getDateTime() const;
    void addItem(Item *item, int quantity);
private:
    QList<PurchaseItem> items;
    Customer *customer;
    QDatetime dateTime;
};

#endif // TRANSACTION_H
