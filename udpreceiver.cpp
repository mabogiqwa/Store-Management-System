#include "udpreceiver.h"

UdpReceiver::UdpReceiver(QObject *parent) : QObject(parent), m_socket(nullptr), m_listening(false)
{
    m_socket = new QUdpSocket(this);
    connect(m_socket, &QUdpSocket::readyRead,
            this, &UdpReceiver::processPendingDatagrams);
}

UdpReceiver::~UdpReceiver()
{
    stopListening();
}

void UdpReceiver::startListening()
{
    if (!m_listening) {
        if (m_socket->bind(QHostAddress::Any, 12345)) {
            m_listening = true;
        }
    }
}

void UdpReceiver::stopListening()
{
    if (m_listening) {
        m_socket->close();
        m_listening = false;
    }
}

void UdpReceiver::processPendingDatagrams()
{
    while (m_socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_socket->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        m_socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QString data = QString::fromUtf8(datagram);
        emit dataReceived(data);
    }
}
