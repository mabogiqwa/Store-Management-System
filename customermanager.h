#ifndef CUSTOMERMANAGER_H
#define CUSTOMERMANAGER_H

#include <QString>
#include <QObject>
#include "customer.h"

class CustomerManager : public QObject
{
    Q_OBJECT
public:
    static CustomerManager* getInstance();

    void addCustomer(const QString &name);
    QList<Customer*> getCustomer() const;
    Customer* findCustomer(const QString &name) const;

signals:
    void customerAdded(Customer *customer);

private:
    explicit CustomerManager(QObject *parent = nullptr);
    ~CustomerManager();

    static CustomerManager *sInstance;
    QList<Customer*> mCustomer;
};

#endif // CUSTOMERMANAGER_H
