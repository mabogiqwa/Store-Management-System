#include "customermanager.h"
#include "customer.h"

CustomerManager* CustomerManager::sInstance = nullptr;

CustomerManager* CustomerManager::getInstance()
{
    if (!sInstance) {
        sInstance = new CustomerManager();
    }
    return sInstance;
}

CustomerManager::CustomerManager(QObject *parent)
    : QObject{parent}
{}

void CustomerManager::addCustomer(const QString &name) {
    if (!findCustomer(name)) {
        Customer *customer = new Customer(name);
        mCustomer.append(customer);
        emit customerAdded(customer);
    }
}

Customer* CustomerManager::findCustomer(const QString &name) const
{
    for (Customer *customer : mCustomers) {
        if (customer->getName() == name) {
            return customer;
        }
    }
    return nullptr;
}

QList<Customer*> CustomerManager::getCustomers() const
{
    return mCustomer;
}

CustomerManager::~CustomerManager() {
    qDeleteAll(mCustomers);
    mCustomers.clear();
}
