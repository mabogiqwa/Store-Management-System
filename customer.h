#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>

class Customer
{
public:
    explicit Customer(const QString &name);
    ~Customer();

    QString getName() const;
    void setName(const QString &name);
private:
    QString customerName;
};

#endif // CUSTOMER_H
