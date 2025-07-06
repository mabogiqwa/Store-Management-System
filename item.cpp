#include "item.h"

Item::Item(const QString &name, ItemType type) : itemName(name), itemtype(type)
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

ItemType Item::getType() const
{
    return itemType;
}
