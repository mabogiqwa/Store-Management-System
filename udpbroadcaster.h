#ifndef UDPBROADCASTER_H
#define UDPBROADCASTER_H

#include <QThread>
#include <QUdpSocket>
#include <QTimer>
#include "transaction.h"
#include "transactionmanager.h"
#include "customer.h"
#include "item.h"
#include <QHostAddress>

class UdpBroadcaster : public QObject
{
    Q_OBJECT
public:
    explicit UdpBroadcaster(QObject *parent = nullptr);
    ~UdpBroadcaster();

    void startBroadcasting();
    void stopBroadcasting();
signals:
    void broadcastSent(const QString &data);
    void dataRequested();
private slots:
    void broadcastData();
    void onThreadStarted();      // private slot
    void onThreadFinished();
private:
    QUdpSocket *mSocket;
    QTimer *mTimer;
    bool mBroadcasting;
    QThread *mThread;
    QString generateXMLData();
};

#endif // UDPBROADCASTER_H
