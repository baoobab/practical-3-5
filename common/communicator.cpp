#include "communicator.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

TCommunicator::TCommunicator(TCommParams& pars, QObject *parent) : QUdpSocket(parent)
{
    params = pars;
    ready = bind(params.rHost, params.rPort,
                 QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
    if (ready) connect(this, SIGNAL(readyRead()), this, SLOT(recieve()));
}

bool TCommunicator::isReady()
{
    return ready;
}

void TCommunicator::send(const QJsonDocument& jsonDoc)
{
    if (ready)
    {
        // // Создаем JSON объект
        // QJsonObject jsonObj;
        // requestObj["messageType"] = static_cast<int>(messageType); // Преобразуем тип сообщения в int
        // jsonObj["data"] = data; // Данные

        // // Преобразуем JSON объект в QByteArray
        // QJsonDocument jsonDoc(jsonObj);

        QByteArray msg = jsonDoc.toJson();

        writeDatagram(msg, params.sHost, params.sPort);
        //qDebug() << "Sent" << msg;
    }
}

void TCommunicator::recieve()
{
    while (hasPendingDatagrams()) // Используем цикл для обработки всех ожидающих датаграмм
    {
        quint64 size = pendingDatagramSize();
        QByteArray msg(size, '\0');
        readDatagram(msg.data(), size);

        // Преобразуем полученное сообщение из JSON
        QJsonDocument jsonDoc = QJsonDocument::fromJson(msg);
        if (jsonDoc.isNull()) {
            // Обработка ошибки парсинга
            qDebug() << "Failed to parse JSON:" << msg;
            return;
        }

        // Проверяем, что это объект JSON
        if (!jsonDoc.isObject()) {
            qDebug() << "Expected a JSON object:" << msg;
            return;
        }

        emit recieved(jsonDoc); // Эмитируем сигнал с полученным JSON документом
    }
}
