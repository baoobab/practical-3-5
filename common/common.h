#ifndef COMMON_H
#define COMMON_H

#include <QString>

// // Перечень доступных запросов для сервера
// enum RequestType
// {
//     CANONICAL_FORM_REQUEST = 1,
//     CLASSICAL_FORM_REQUEST,
//     CHANGE_ROOTS_COUNT_REQUEST,
//     CHANGE_ROOT_AND_AN_REQUEST,
//     CALCULATE_VALUE_AT_X_REQUEST,
//     SET_NEW_POLYNOMIAL_REQUEST
// };

// // Перечень ответов от сервера
// enum ResponseType
// {
//     CANONICAL_FORM_ANSWER = 1,
//     CLASSICAL_FORM_ANSWER,
//     CHANGE_ROOTS_COUNT_ANSWER,
//     CHANGE_ROOT_AND_AN_ANSWER,
//     CALCULATE_VALUE_AT_X_ANSWER,
//     SET_NEW_POLYNOMIAL_ANSWER,
//     ERROR_UNKNOWN_REQUEST = -1 // Для обработки неизвестных запросов
// };

// Перечень возможных сообщений
enum MessageType
{
    CANONICAL_FORM_MESSAGE = 1,
    CLASSICAL_FORM_MESSAGE,
    CHANGE_ROOTS_COUNT_MESSAGE,
    CHANGE_ROOT_AND_AN_MESSAGE,
    CALCULATE_VALUE_AT_X_MESSAGE,
    SET_NEW_POLYNOMIAL_MESSAGE,
    ERROR_UNKNOWN_MESSAGE = -1 // Для обработки неизвестных сообщений
};

// Перечень доступных типов данных, которые используются при обмене сообщениями
// можно найти в классе QJsonValue


// extern const QChar separator;
// QString& operator<< (QString&,const QString&);

#endif // COMMON_H
