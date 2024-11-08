#include "interface.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include "common.h"

TInterface::TInterface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Многочлен на комплексных числах");
    setMaximumSize(600, 300);

    // Создаём метку и поле вывода
    outputField = new QLineEdit(this);
    outputField->setReadOnly(true);
    outputField->setPlaceholderText("Результат любого пункта будет здесь...");
    outputField->setMaximumWidth(350);

    // Кнопка "Очистить"
    QPushButton *clearButton = new QPushButton("Очистить", this);
    connect(clearButton, &QPushButton::clicked, this, &TInterface::clearOutput);

    // Создаем горизонтальный макет для метки и поля вывода
    QHBoxLayout *outputLayout = new QHBoxLayout();
    outputLayout->addWidget(outputField);
    outputLayout->addWidget(clearButton);

    // Создаем вертикальный макет для всего интерфейса
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(outputLayout);

    // Пункт 1: Вывод канонического вида полинома
    QLabel *canonicalFormLabel = new QLabel("Вывод канонического вида полинома", this);
    QPushButton *canonicalFormButton = new QPushButton("Вывести", this);
    connect(canonicalFormButton, &QPushButton::clicked, this, &TInterface::sendCanonicalFormRequest);

    QHBoxLayout *canonicalFormLayout = new QHBoxLayout();
    canonicalFormLayout->addWidget(canonicalFormLabel);
    canonicalFormLayout->addWidget(canonicalFormButton);
    mainLayout->addLayout(canonicalFormLayout);

    // Пункт 2: Вывод классического вида полинома
    QLabel *classicalFormLabel = new QLabel("Вывод классического вида полинома", this);
    QPushButton *classicalFormButton = new QPushButton("Вывести", this);
    connect(classicalFormButton, &QPushButton::clicked, this, &TInterface::sendClassicalFormRequest);

    QHBoxLayout *classicalFormLayout = new QHBoxLayout();
    classicalFormLayout->addWidget(classicalFormLabel);
    classicalFormLayout->addWidget(classicalFormButton);
    mainLayout->addLayout(classicalFormLayout);

    // Пункт 3: Изменение количества корней
    QLabel *changeRootsCountLabel = new QLabel("Изменение количества корней", this);
    QLineEdit *changeRootsCountInput = new QLineEdit(this);

    QPushButton *changeRootsCountButton = new QPushButton("Изменить", this);
    connect(changeRootsCountButton, &QPushButton::clicked, [this, changeRootsCountInput]() {
        QString inputText = changeRootsCountInput->text();
        sendChangeRootsCountRequest(inputText);
        changeRootsCountInput->clear();
    });

    QHBoxLayout *changeRootsCountLayout = new QHBoxLayout();
    changeRootsCountLayout->addWidget(changeRootsCountLabel);
    changeRootsCountLayout->addWidget(changeRootsCountInput);
    changeRootsCountLayout->addWidget(changeRootsCountButton);

    mainLayout->addLayout(changeRootsCountLayout);

    // Пункт 4: Изменить a_n и корень по индексу
    QLabel *newANAndRootsLabel = new QLabel("Изменить a_n и корень по индексу", this);

    QLineEdit *newANInput = new QLineEdit(this);
    newANInput->setPlaceholderText("Новый a_n");

    QLineEdit *newRootIndexInput = new QLineEdit(this);
    newRootIndexInput->setPlaceholderText("Индекс корня");

    QPushButton *newANAndRootsButton = new QPushButton("Изменить", this);

    connect(newANAndRootsButton, &QPushButton::clicked, [this, newANInput, newRootIndexInput]() {
        QString anText = newANInput->text();
        QString indexText = newRootIndexInput->text();
        sendChangeRootAndANRequest(anText + " " + indexText);
        newANInput->clear();
        newRootIndexInput->clear();
    });

    QHBoxLayout *newANAndRootsLayout = new QHBoxLayout();
    newANAndRootsLayout->addWidget(newANAndRootsLabel);
    newANAndRootsLayout->addWidget(newANInput);
    newANAndRootsLayout->addWidget(newRootIndexInput);
    newANAndRootsLayout->addWidget(newANAndRootsButton);

    mainLayout->addLayout(newANAndRootsLayout);

    // Пункт 5: Вычислить значение в точке x
    QLabel *calculateValueAtXLabel = new QLabel("Вычислить значение в точке x", this);
    QLineEdit *calculateValueAtXInput = new QLineEdit(this);

    QPushButton *calculateValueAtXButton = new QPushButton("Вычислить", this);
    connect(calculateValueAtXButton, &QPushButton::clicked, [this, calculateValueAtXInput]() {
        QString inputText = calculateValueAtXInput->text();
        sendCalculateValueAtXRequest(inputText);
        calculateValueAtXInput->clear();
    });

    QHBoxLayout *calculateValueAtXLayout = new QHBoxLayout();
    calculateValueAtXLayout->addWidget(calculateValueAtXLabel);
    calculateValueAtXLayout->addWidget(calculateValueAtXInput);
    calculateValueAtXLayout->addWidget(calculateValueAtXButton);

    mainLayout->addLayout(calculateValueAtXLayout);

    // Пункт 6: Задать новый полином
    QLabel *setNewPolynomialLabel = new QLabel("Задать новый полином", this);
    QLineEdit *setNewPolynomialANInput = new QLineEdit(this);
    setNewPolynomialANInput->setPlaceholderText("a_n");

    QLineEdit *setNewPolynomialRootsInput = new QLineEdit(this);
    setNewPolynomialRootsInput->setPlaceholderText("корни (через пробел)");

    QPushButton *setNewPolynomialButton = new QPushButton("Задать", this);

    connect(setNewPolynomialButton, &QPushButton::clicked, [this, setNewPolynomialANInput, setNewPolynomialRootsInput]() {
        QString anText = setNewPolynomialANInput->text();
        QString rootsText = setNewPolynomialRootsInput->text();
        sendSetNewPolynomialRequest(anText + " " + rootsText);
        setNewPolynomialANInput->clear();
        setNewPolynomialRootsInput->clear();
    });

    QHBoxLayout *setNewPolynomialLayout = new QHBoxLayout();
    setNewPolynomialLayout->addWidget(setNewPolynomialLabel);
    setNewPolynomialLayout->addWidget(setNewPolynomialANInput);
    setNewPolynomialLayout->addWidget(setNewPolynomialRootsInput);
    setNewPolynomialLayout->addWidget(setNewPolynomialButton);

    mainLayout->addLayout(setNewPolynomialLayout);

    // Добавляем кнопку "Выход"
    QPushButton *exitButton = new QPushButton("Выход", this);
    mainLayout->addWidget(exitButton);

    connect(exitButton, &QPushButton::clicked, this, &TInterface::exitApplication);

    // Установка основного макета
    setLayout(mainLayout);
}

TInterface::~TInterface()
{
    // TODO: ПО ЕГОРИКУ ДЕЛИТОВ НАКИДАТЬ СЮДА
}

void TInterface::sendCanonicalFormRequest()
{
    formRequest(CANONICAL_FORM_REQUEST); // Отправляем запрос на вывод канонического вида
}

void TInterface::sendClassicalFormRequest()
{
    formRequest(CLASSICAL_FORM_REQUEST); // Отправляем запрос на вывод классического вида
}

void TInterface::sendChangeRootsCountRequest(const QString& count)
{
    formRequest(CHANGE_ROOTS_COUNT_REQUEST, count); // Отправляем запрос на изменение количества корней с параметром count.
}

void TInterface::sendChangeRootAndANRequest(const QString& data)
{
    formRequest(CHANGE_ROOT_AND_AN_REQUEST, data); // Отправляем запрос на изменение a_n и корня с параметром data.
}

void TInterface::sendCalculateValueAtXRequest(const QString& x)
{
    formRequest(CALCULATE_VALUE_AT_X_REQUEST, x); // Отправляем запрос на вычисление значения в точке x с параметром x.
}

void TInterface::sendSetNewPolynomialRequest(const QString& data)
{
    formRequest(SET_NEW_POLYNOMIAL_REQUEST, data); // Отправляем запрос на задание нового полинома с параметром data.
}

void TInterface::formRequest(RequestType requestType, const QString& params)
{
    emit request(QString::number(requestType) + (params.isEmpty() ? "" : " " + params));
    // Эмитируем сигнал запроса для отправки на сервер.
}

void TInterface::answer(const QString& response)
{
    if (response.startsWith("POLYNOM:")) {
        QString polynomData = response.mid(8);
        outputField->setText("Получен новый полином: " + polynomData);
    } else {
        outputField->setText(response);
    }
}

void TInterface::clearOutput()
{
    outputField->clear(); // Очистка поля вывода
}

void TInterface::exitApplication()
{
    QApplication::quit(); // Завершение приложения
}
