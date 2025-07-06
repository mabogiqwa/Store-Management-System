#ifndef ITEM_H
#define ITEM_H

enum class Itemtype {
    Book,
    Magazine
};

class Item
{
public:
    explicit Item(const QString &name, ItemType type);
    ~Item();

    QString getName() const;
    void setName(const QString &name);

    ItemType getType() const;
    void setType(ItemType type);

    QString getTypeString() const;
private:
    QString itemName;
    ItemType itemType;
};

#endif // ITEM_H
