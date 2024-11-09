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
    QString answer; // Тут будет ответ
    QString strMsg = QString(msg); // Извлечение параметров из сообщения

    char separatorChar = separator.toLatin1(); // Преобразование QChar в char
    int pos = strMsg.indexOf(separatorChar);

    // Проверка на наличие разделителя
    if (pos == -1) {
        qDebug() << "Separator not found in message.";
        return; // Обработка случая, когда разделитель не найден
    }

    int requestType = strMsg.left(pos).toInt(); // Получаем тип запроса

    strMsg = strMsg.mid(pos + 1); // Убираем тип запроса из сообщения

    // Проверяем, начинается ли параметр "P(x) = "
    const QString prefix = "P(x) = ";
    if (!strMsg.startsWith(prefix)) {
        // Иначе ошибка, тк полином должен идти первым параметром
        qDebug() << "Polynom not found as first param in message.";
        return;
    }

    QString param = strMsg.mid(0, strMsg.indexOf(separatorChar)); // Получаем первый параметр - это должен быть полином
    TPolynom p(param); // Создание полинома
    strMsg.remove(0, strMsg.indexOf(separatorChar) + 1); // Убираем полином из сообщения

    switch (requestType)
    {
    case CANONICAL_FORM_REQUEST:
    {
        p.setPrintMode(EPrintMode::EPrintModeCanonical);
        answer << QString().setNum(CANONICAL_FORM_ANSWER) << p;
        break;
    }
    case CLASSICAL_FORM_REQUEST:
    {
        p.setPrintMode(EPrintMode::EPrintModeClassic);
        answer << QString().setNum(CLASSICAL_FORM_ANSWER) << p;
        break;
    }
    case CHANGE_ROOTS_COUNT_REQUEST:
    {

        int newRootsCount;
        newRootsCount = msg.toInt(); // Получаем новое количество корней
        // логика обработки корней
        answer << QString().setNum(CHANGE_ROOTS_COUNT_ANSWER) << "Количество корней изменено.";
        break;
    }
    case CHANGE_ROOT_REQUEST:
    {
        QString index = strMsg.mid(0, strMsg.indexOf(separatorChar)); // Первый параметр (после полинома) - индекс
        QString strNewRoot = strMsg.mid(strMsg.indexOf(separatorChar)); // Второй параметр (после полинома) - сам корень
        number newRoot;
        strNewRoot >> newRoot;
        p.changeRootByIndex(index.toInt(), newRoot);
        p.setPrintMode(EPrintMode::EPrintModeClassic); // Ставим классик принт мод для норм отображения

        answer << QString().setNum(CHANGE_ROOT_ANSWER) << p;
        break;
    }

    case CALCULATE_VALUE_AT_X_REQUEST:
    {
        answer << QString().setNum(CALCULATE_VALUE_AT_X_ANSWER) << p.value(0);
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
    case SET_CANONIC_COEF_REQUEST:
    {
        number newCanonicCoef;
        strMsg >> newCanonicCoef; // Единственный параметр (после полинома) - канон. коэф

        p.setCanonicCoef(newCanonicCoef);
        p.setPrintMode(EPrintMode::EPrintModeClassic); // Ставим классик принт мод для норм отображения

        answer << QString().setNum(SET_CANONIC_COEF_ANSWER) << p;
        break;
    }
    default:
    {
        answer << "Неизвестный запрос.";
        break;
    }
    }

    qDebug() << "Sending response:" << answer; // Логируем ответ перед отправкой
    comm->send(QByteArray().append(answer.toUtf8())); // Отправляем ответ обратно клиенту answer.toUtf8()
}
