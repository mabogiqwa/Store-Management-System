#include "udpbroadcaster.h"
#include <QDebug>

UdpBroadcaster::UdpBroadcaster(QObject *parent)
    : QObject(parent), mSocket(nullptr), mTimer(nullptr), mBroadcasting(false)
{
    // Create objects in the main thread - no threading complications
    mSocket = new QUdpSocket(this);
    mTimer = new QTimer(this);

    // Connect the timer to broadcast function
    connect(mTimer, &QTimer::timeout, this, &UdpBroadcaster::broadcastData);
}

UdpBroadcaster::~UdpBroadcaster() {
    stopBroadcasting();
}

void UdpBroadcaster::startBroadcasting()
{
    qDebug() << "startBroadcasting() was executed";

    if (mBroadcasting) {
        qDebug() << "Already broadcasting";
        return;
    }

    mBroadcasting = true;

    if (mTimer) {
        mTimer->start(5000); // Broadcast every 5 seconds
        qDebug() << "Timer started - broadcasting every 5 seconds";
    }

    qDebug() << "Finished executing startBroadcasting()";
}

void UdpBroadcaster::stopBroadcasting()
{
    qDebug() << "stopBroadcasting() was called";

    if (!mBroadcasting) {
        qDebug() << "Not currently broadcasting";
        return;
    }

    mBroadcasting = false;

    if (mTimer) {
        mTimer->stop();
        qDebug() << "Timer stopped";
    }

    qDebug() << "Broadcasting stopped successfully";
}

void UdpBroadcaster::broadcastData()
{
    if (!mBroadcasting || !mSocket) {
        return;
    }

    qDebug() << "Broadcasting data...";

    QString xmlData = generateXMLData();
    QByteArray data = xmlData.toUtf8();

    qint64 bytesWritten = mSocket->writeDatagram(data, QHostAddress::Broadcast, 12345);

    if (bytesWritten != -1) {
        qDebug() << "Broadcast sent successfully:" << bytesWritten << "bytes";
        emit broadcastSent(xmlData);
    } else {
        qDebug() << "Failed to send broadcast";
    }
}

QString UdpBroadcaster::generateXMLData()
{
    QString xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    xml += "<transactions>\n";

    TransactionManager *transactionManager = TransactionManager::getInstance();
    if (!transactionManager) {
        qDebug() << "TransactionManager is null";
        xml += "</transactions>";
        return xml;
    }

    QList<Transaction*> transactions = transactionManager->getTransactions();
    qDebug() << "Found" << transactions.size() << "transactions to broadcast";

    for (Transaction *transaction : transactions) {
        if (!transaction || !transaction->getCustomer()) {
            continue;
        }

        xml += "  <transaction>\n";
        xml += QString("   <customer>%1</customer>\n").arg(transaction->getCustomer()->getName());
        xml += QString("   <datetime>%1</datetime>\n").arg(transaction->getDateTime().toString(Qt::ISODate));
        xml += "   <items>\n";

        for (const PurchaseItem &item : transaction->getItems()) {
            if (!item.item) {
                continue;
            }
            xml += "     <item>\n";
            xml += QString("      <name>%1</name>\n").arg(item.item->getName());
            xml += QString("      <quantity>%1</quantity>\n").arg(item.quantity);
            xml += "     </item>\n";
        }

        xml += "   </items>\n";
        xml += "  </transaction>\n";
    }

    xml += "</transactions>";

    return xml;
}
