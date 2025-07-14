#include "udpbroadcaster.h"

UdpBroadcaster::UdpBroadcaster(QObject *parent) : QThread(parent), mSocket(nullptr), mTimer(nullptr), mBroadcasting(false)
{

}

UdpBroadcaster::~UdpBroadcaster() {
    stopBroadcasting();
    if (isRunning()) {
        quit();
        wait();
    }
}

void UdpBroadcaster::startBroadcasting()
{
    stopBroadcasting();
    if (isRunning()) {
        quit();
        wait();
    }
}

void UdpBroadcaster::stopBroadcasting()
{
    if (!mBroadcasting) {
        mBroadcasting = true;
        start();
    }
}

void UdpBroadcaster::run()
{
    mSocket = new QUdpSocket();
    mTimer = new QTimer();

    connect(mTimer, &QTimer::timeout, this, &UdpBroadcaster::broadcastData);

    mTimer->start(5000);

    exec();

    delete mSocket;
    delete mTimer;
    mSocket = nullptr;
    mTimer = nullptr;
}

void UdpBroadcaster::broadcastData()
{
    if (!mBroadcasting || mSocket) {
        return;
    }
    QString xmlData = generateXMLData();
    QByteArray data = xmlData.toUtf8();

    mSocket->writeDatagram(data, QHostAddress::Broadcast, 12345);

    emit broadcastSent(xmlData);
}

QString UdpBroadcaster::generateXMLData()
{
    //QString xml = "<?xml"
}
