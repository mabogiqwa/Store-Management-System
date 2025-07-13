#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <QObject>

class ItemManager : public QObject
{
    Q_OBJECT
public:
    explicit ItemManager(QObject *parent = nullptr);

signals:
};

#endif // ITEMMANAGER_H
