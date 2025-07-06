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

void Item::setType(ItemType type)
{
    itemType = type;
}

QString Item::getTypeString() const
{
    if (itemType == ItemType::Book)
        return "Book";
    else if (itemType == ItemType::Magazine)
        return "Magazine";
    else
        return "Unknown";
}
