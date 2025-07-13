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

}

void UdpBroadcaster::stopBroadcasting()
{

}

void UdpBroadcaster::run()
{

}

void UdpBroadcaster::broadcastData()
{

}

QString UdpBroadcaster::generateXMLData()
{

}
