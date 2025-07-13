#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <QObject>
#include "item.h"
#include <QString>
#include <QList>

class ItemManager : public QObject
{
    Q_OBJECT
public:
    static ItemManager* getInstance();

    void addItem(const QString &name, Itemtype type);
    QList<Item*> getItems() const;
    Item* findItem(const QString &name) const;

    void createBackup();
    void restoreFromBackup();

signals:
    void itemAdded(Item *item);
    void itemsRestored();

private:
    explicit ItemManager(QObject *parent = nullptr);
    ~ItemManager();

    static ItemManager *sInstance;
    QList<Item*> mItems;
    QList<Item*> mBackup;
};

#endif // ITEMMANAGER_H
