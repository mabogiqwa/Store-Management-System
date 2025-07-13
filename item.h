#ifndef ITEM_H
#define ITEM_H

#include <QString>
//#include <ItemType>

enum class Itemtype {
    Book,
    Magazine
};

class Item
{
public:
    explicit Item(const QString &name, Itemtype type);
    ~Item();

    QString getName() const;
    void setName(const QString &name);

    Itemtype getType() const;
    void setType(Itemtype type);

    QString getTypeString() const;
private:
    QString itemName;
    Itemtype itemType;
};

#endif // ITEM_H
