#include "application.h"
#include "polynom.h"
#include "common.h"
#include "number.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

TApplication::TApplication(int argc, char *argv[])
    : QCoreApplication(argc, argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10000,
                        QHostAddress("127.0.0.1"), 10001 };
    comm = new TCommunicator(pars, this);

    connect(comm, SIGNAL(recieved(QJsonDocument)), this, SLOT(recieve(QJsonDocument)));
}

void TApplication::recieve(QJsonDocument jsonDoc)
{
    if (jsonDoc.isNull()) {
        qDebug() << "Received an empty or invalid JSON document.";
        return;
    }

    // Извлекаем объект из JSON-документа
    QJsonObject jsonObj = jsonDoc.object();

    // Проверяем тип запроса
    if (!jsonObj.contains("messageType")) {
        QJsonObject errObj;
        errObj["messageType"] = ERROR_UNKNOWN_MESSAGE;
        QJsonDocument jsonDoc(errObj);
        comm->send(jsonDoc); // Отправляем ответ об ошибке обратно
        return;
    }
    // Проверяем данные в запросе
    if (!jsonObj.contains("data")) {
        QJsonObject errObj;
        errObj["messageType"] = ERROR_UNKNOWN_MESSAGE; // TODO: мб вынести ошибки отдельно
        QJsonDocument jsonDoc(errObj);
        comm->send(jsonDoc); // Отправляем ответ об ошибке обратно
        return;
    }

    int messageType = jsonObj["messageType"].toInt();
    // Создаем JSON объект для ответа
    QJsonObject answerObj;
    QJsonObject answerDataObj;
    answerObj["messageType"] = messageType;

    // Создание полинома (можно передавать параметры через JSON при необходимости)
    TPolynom p;

    switch (messageType)
    {
    case CANONICAL_FORM_MESSAGE:
        p.setPrintMode(EPrintMode::EPrintModeCanonical);
        answerDataObj["pCanonicCoef"] = 52;
        break;

    case CLASSICAL_FORM_MESSAGE:
        p.setPrintMode(EPrintMode::EPrintModeClassic);
        answerDataObj["pCanonicCoef"] = 5333;
        break;

    case CHANGE_ROOTS_COUNT_MESSAGE:
    {

        // Логика обработки изменения количества корней
        break;
    }

    case CHANGE_ROOT_AND_AN_MESSAGE:
    {

        // Логика изменения a_n и корня должна быть реализована в классе TPolynom
        break;
    }

    case CALCULATE_VALUE_AT_X_MESSAGE:
    {
        // Логика
        break;
    }

    case SET_NEW_POLYNOMIAL_MESSAGE:
    {
        // Логика задания нового полинома должна быть реализована в классе TPolynom
        break;
    }

    default:
        answerDataObj["pCanonicCoef"] = 0;
        break;
    }

    // Преобразуем JSON объект в строку
    answerObj["data"] = answerDataObj;
    QJsonDocument jsonAnswerDoc(answerObj);

    comm->send(jsonAnswerDoc); // Отправляем ответ обратно клиенту
}
