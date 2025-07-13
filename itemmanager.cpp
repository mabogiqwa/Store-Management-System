#include "itemmanager.h"

ItemManager* ItemManager::sInstance = nullptr;

ItemManager::ItemManager(QObject *parent)
    : QObject{parent}
{}

ItemManager* ItemManager::getInstance() {
    if (!sInstance) {
        sInstance = new ItemManager();
    }

    return sInstance;
}

ItemManager::~ItemManager() {
    qDeleteAll(mItems);
    mItems.clear();
    qDeleteAll(mBackup);
    mBackup.clear();
}
