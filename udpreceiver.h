#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

class UdpReceiver : public QObject
{
    Q_OBJECT

public:
    explicit UdpReceiver(QObject *parent = nullptr);
    ~UdpReceiver();

    void startListening();
    void stopListening();

signals:
    void dataReceived(const QString &data);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket *m_socket;
    bool m_listening;
};

#endif
