#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "common.h"

class TInterface : public QWidget
{
    Q_OBJECT

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

public slots:
    void clearOutput(); // Очистить поле вывода
    void sendCanonicalFormRequest(); // Отправить запрос на вывод канонического вида полинома
    void sendClassicalFormRequest(); // Отправить запрос на вывод классического вида полинома
    void sendChangeRootsCountRequest(const QString& inputText); // Отправить запрос на изменение количества корней
    void sendCalculateValueAtXRequest(const QString& x); // Отправить запрос на вычисление значения в точке x
    void sendSetNewPolynomialRequest(QString& anText, QString& rootsText); // Отправить запрос на задание нового полинома
    void sendChangeRootAndANRequest(QString& anText, QString& indexText); // Отправить запрос на изменение a_n и корня по индексу
    void exitApplication(); // Выход из приложения
    void answer(const QString& response); // Обработка ответа от сервера

signals:
    void request(QString);
private:
    QLineEdit *outputField; // Поле для вывода результатов

    // Layouts and UI elements for various functionalities
    QVBoxLayout *mainLayout; // Основной вертикальный макет

    void formRequest(RequestType requestType, const QString& params = ""); // Метод для отправки запроса на сервер с параметрами
};

#endif // INTERFACE_H
