#include "application.h"
#include "polynom.h"
#include "common.h"
#include "number.h"

TApplication::TApplication(int argc, char *argv[])
    : QCoreApplication(argc, argv)
{
    TCommParams pars = { QHostAddress("127.0.0.1"), 10000,
                        QHostAddress("127.0.0.1"), 10001 };
    comm = new TCommunicator(pars, this);

    connect(comm, SIGNAL(recieved(QByteArray)), this, SLOT(recieve(QByteArray)));
}

void TApplication::recieve(QByteArray msg)
{
    QString answer;
    number root;

    // Извлечение параметров из сообщения
    QString strMsg = QString(msg);
    strMsg >> root;

    TPolynom p; // Создание полинома

    char separatorChar = separator.toLatin1(); // Преобразование QChar в char
    int pos = msg.indexOf(separatorChar);

    // Проверка на наличие разделителя
    if (pos == -1) {
        return; // Обработка случая, когда разделитель не найден
    }

    int requestType = msg.left(pos).toInt();
    msg = msg.mid(pos + 1); // Убираем тип запроса из сообщения

    switch (requestType)
    {
    case CANONICAL_FORM_REQUEST:
        p.setPrintMode(EPrintMode::EPrintModeCanonical);
        answer << QString().setNum(CANONICAL_FORM_ANSWER) << p;
        break;

    case CLASSICAL_FORM_REQUEST:
        p.setPrintMode(EPrintMode::EPrintModeClassic);
        answer << QString().setNum(CLASSICAL_FORM_ANSWER) << p;
        break;

    case CHANGE_ROOTS_COUNT_REQUEST:
    {
        int newRootsCount;
        newRootsCount = msg.toInt(); // Получаем новое количество корней
        // логика обработки корней
        answer << QString().setNum(CHANGE_ROOTS_COUNT_ANSWER) << "Количество корней изменено.";
        break;
    }

    case CHANGE_ROOT_AND_AN_REQUEST:
    {
        QString rootChangeData;
        rootChangeData = strMsg; // Ожидаем данные для изменения a_n и корня
        // Логика изменения a_n и корня должна быть реализована в классе TPolinom
        answer << QString().setNum(CHANGE_ROOT_AND_AN_ANSWER) << "Изменение выполнено.";
        break;
    }

    case CALCULATE_VALUE_AT_X_REQUEST:
    {
        strMsg >> root; // Получаем значение x
        answer << QString().setNum(CALCULATE_VALUE_AT_X_ANSWER) << root << p.value(root);
        break;
    }

    case SET_NEW_POLYNOMIAL_REQUEST:
    {
        QString newPolynomialData;
        newPolynomialData = strMsg; // Ожидаем данные для нового полинома
        // Логика задания нового полинома должна быть реализована в классе TPolinom
        answer << QString().setNum(SET_NEW_POLYNOMIAL_ANSWER) << "Новый полином установлен.";
        break;
    }

    default:
        answer << QString().setNum(ERROR_UNKNOWN_REQUEST) << "Неизвестный запрос.";
        break;
    }

    comm->send(QByteArray().append(answer.toUtf8())); // Отправляем ответ обратно клиенту
}
