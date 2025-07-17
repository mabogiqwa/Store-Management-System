#include "udpbroadcaster.h"
#include <QDebug>

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
    qDebug() << "startBroadcasting() was executed";
    stopBroadcasting();

    if (isRunning()) {
        quit();
        wait();
    }
    qDebug() << "Finished executing startBroadcasting()";
}

void UdpBroadcaster::stopBroadcasting()
{
    qDebug() << "stopBroadcasting() was called";
    if (mBroadcasting) {
        qDebug() << "mBroadcasting is not nullptr";
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
    QString xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    xml += "<transactions>\n";

    TransactionManager *transactionManager = TransactionManager::getInstance();
    QList<Transaction*> transactions = transactionManager->getTransactions();

    for (Transaction *transaction : transactions) {
        xml += "  <transaction>\n";
        xml += QString("   <customer>%1</customer>\n").arg(transaction->getCustomer()->getName());
        xml += QString("   <datetime>%1</datetime>\n").arg(transaction->getDateTime().toString(Qt::ISODate));
        xml += "   <items>\n";

        for (const PurchaseItem &item : transaction->getItems()) {
            xml += "   <item>\n";
            xml += QString("    <name>%1</name>\n").arg(item.item->getName());
            xml += QString("    <quantity>%1</quantity>\n").arg(item.quantity);
            xml += "    </item>\n";
        }

        xml += "   </items>\n";
        xml += "  </transaction>\n";
    }

    xml += "</transactions>";

    return xml;
}
