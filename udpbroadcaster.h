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

class UdpBroadcaster : public QThread
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
protected:
    void run() override;

private slots:
    void broadcastData();
private:
    QUdpSocket *mSocket;
    QTimer *mTimer;
    bool mBroadcasting;
    QString generateXMLData();
};

#endif // UDPBROADCASTER_H
