#include "transaction.h"
#include "customer.h"
#include "item.h"

Transaction::Transaction(Customer *cstmer, const QDateTime &dT)
{
    customer = cstmer;
    dateTime = dT;
}

Transaction::~Transaction()
{
}

Customer* Transaction::getCustomer() const
{
    return customer;
}

QDateTime Transaction::getDateTime() const
{
    return dateTime;
}

void Transaction::addItem(Item *item, int quantity)
{
    items.append(PurchaseItem(item, quantity));
}

QList<PurchaseItem> Transaction::getItems() const
{
    return items;
}
