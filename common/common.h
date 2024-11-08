#ifndef COMMON_H
#define COMMON_H

#include <QString>

enum RequestType
{
    CANONICAL_FORM_REQUEST = 1,
    CLASSICAL_FORM_REQUEST,
    CHANGE_ROOTS_COUNT_REQUEST,
    CHANGE_ROOT_AND_AN_REQUEST,
    CALCULATE_VALUE_AT_X_REQUEST,
    SET_NEW_POLYNOMIAL_REQUEST
};
enum ResponseType {
    CANONICAL_FORM_ANSWER = 1,
    CLASSICAL_FORM_ANSWER,
    CHANGE_ROOTS_COUNT_ANSWER,
    CHANGE_ROOT_AND_AN_ANSWER,
    CALCULATE_VALUE_AT_X_ANSWER,
    SET_NEW_POLYNOMIAL_ANSWER,
    ERROR_UNKNOWN_REQUEST = -1 // Для обработки неизвестных запросов
};

extern const QChar separator;
QString& operator<< (QString&,const QString&);

#endif // COMMON_H
