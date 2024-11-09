#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include "common.h"

struct TCommParams
{
    QHostAddress rHost;
    quint16      rPort;
    QHostAddress sHost;
    quint16      sPort;
};

class TCommunicator : public QUdpSocket
{
    Q_OBJECT

    bool         ready;
    TCommParams  params;

public:
    TCommunicator(TCommParams&, QObject *parent = nullptr);
    bool isReady();

signals:
    void recieved(QJsonDocument); // Изменено на QJsonDocument

public slots:
    void send(const QJsonDocument& jsonDoc); // Обновлено для передачи в JSON
private slots:
    void recieve();
};

#endif // COMMUNICATOR_H
