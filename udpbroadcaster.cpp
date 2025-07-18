#include "udpbroadcaster.h"
#include <QDebug>

UdpBroadcaster::UdpBroadcaster(QObject *parent) : QObject(parent), mSocket(nullptr), mTimer(nullptr), mBroadcasting(false), mThread(nullptr)
{
    mSocket = new QUdpSocket();
    mTimer = new QTimer();
    mThread = new QThread();

    this->moveToThread(mThread);
    mSocket->moveToThread(mThread);
    mTimer->moveToThread(mThread);

    connect(mTimer, &QTimer::timeout, this, &UdpBroadcaster::broadcastData);
    connect(mThread, &QThread::started, this, &UdpBroadcaster::onThreadStarted);
    connect(mThread, &QThread::finished, this, &UdpBroadcaster::onThreadFinished);
}

UdpBroadcaster::~UdpBroadcaster() {
    stopBroadcasting();

    if (mThread && mThread->isRunning()) {
        mThread->quit();
        mThread->wait();
    }

    delete mSocket;
    delete mTimer;
    delete mThread;
}

void UdpBroadcaster::startBroadcasting()
{
    qDebug() << "startBroadcasting() was executed";
    if (mBroadcasting) {
        return;
    }

    mBroadcasting = true;

    if (mThread && !mThread->isRunning()) {
        mThread->start();
    }
    qDebug() << "Finished executing startBroadcasting()";
}

void UdpBroadcaster::stopBroadcasting()
{
    qDebug() << "stopBroadcasting() was called";
    if (mBroadcasting) {
        qDebug() << "stopping broadcasting";
        mBroadcasting = false;

        if (mTimer) {
            QMetaObject::invokeMethod(mTimer,"stop",Qt::QueuedConnection);
        }

        if (mThread && mThread->isRunning()) {
            mThread->quit();
            mThread->wait();
        }
    }
}

void UdpBroadcaster::onThreadStarted() {
    qDebug() << "Thread started, beginning broadcast timer";
    if (mTimer) {
        mTimer->start(5000);
    }
}

void UdpBroadcaster::onThreadFinished() {
    qDebug() << "Thread finished";
    if (mTimer) {
        mTimer->stop();
    }
}



void UdpBroadcaster::broadcastData()
{
    if (!mBroadcasting || !mSocket) {
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
    if (!transactionManager) {
        xml += "</transactions>";
        return xml;
    }

    QList<Transaction*> transactions = transactionManager->getTransactions();

    for (Transaction *transaction : transactions) {
        xml += "  <transaction>\n";
        xml += QString("   <customer>%1</customer>\n").arg(transaction->getCustomer()->getName());
        xml += QString("   <datetime>%1</datetime>\n").arg(transaction->getDateTime().toString(Qt::ISODate));
        xml += "   <items>\n";

        for (const PurchaseItem &item : transaction->getItems()) {
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
