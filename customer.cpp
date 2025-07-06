#include "customer.h"

Customer::Customer(const QString &name) : customerName(name)
{

}

Customer::~Customer()
{

}

QString Customer::getName() const
{
    return customerName;
}

void Customer::setName(const QString &name)
{
    customerName = name;
}
