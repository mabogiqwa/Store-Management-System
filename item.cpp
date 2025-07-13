#include "item.h"

Item::Item(const QString &name, Itemtype type) : itemName(name), itemType(type)
{

}

Item::~Item()
{

}

QString Item::getName() const
{
    return itemName;
}

void Item::setName(const QString &name)
{
    itemName = name;
}

Itemtype Item::getType() const
{
    return itemType;
}

void Item::setType(Itemtype type)
{
    itemType = type;
}

QString Item::getTypeString() const
{
    if (itemType == Itemtype::Book)
        return "Book";
    else if (itemType == Itemtype::Magazine)
        return "Magazine";
    else
        return "Unknown";
}
