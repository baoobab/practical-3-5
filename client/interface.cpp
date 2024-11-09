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
    outputField = new QLineEdit(this); // Поле вывода в одну строку
    outputField->setReadOnly(true); // Делаем поле вывода только для чтения
    outputField->setPlaceholderText("Результат любого пункта будет здесь..."); // Подсказка для пользователя
    outputField->setMaximumWidth(350); // Ограничиваем ширину поля вывода

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
    connect(canonicalFormButton, &QPushButton::clicked, this, &TInterface::showCanonicalForm);
    QHBoxLayout *canonicalFormLayout = new QHBoxLayout();
    canonicalFormLayout->addWidget(canonicalFormLabel);
    canonicalFormLayout->addWidget(canonicalFormButton);
    mainLayout->addLayout(canonicalFormLayout);

    // Пункт 2: Вывод классического вида полинома
    QLabel *classicalFormLabel = new QLabel("Вывод классического вида полинома", this);
    QPushButton *classicalFormButton = new QPushButton("Вывести", this);
    connect(classicalFormButton, &QPushButton::clicked, this, &TInterface::showClassicalForm);
    QHBoxLayout *classicalFormLayout = new QHBoxLayout();
    classicalFormLayout->addWidget(classicalFormLabel);
    classicalFormLayout->addWidget(classicalFormButton);
    mainLayout->addLayout(classicalFormLayout);

    // Пункт 3: Изменение количества корней
    QLabel *changeRootsCountLabel = new QLabel("Изменение количества корней", this);
    QLineEdit *changeRootsCountInput = new QLineEdit(this);
    changeRootsCountInput->setPlaceholderText("Новое количество корней");
    QPushButton *changeRootsCountButton = new QPushButton("Изменить", this);
    connect(changeRootsCountButton, &QPushButton::clicked, this, [this, changeRootsCountInput]() {
        QString inputText = changeRootsCountInput->text();
        changeRootsCount(inputText);
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
    newANInput->setMaximumWidth(80);
    QLineEdit *newRootIndexInput = new QLineEdit(this);
    newRootIndexInput->setPlaceholderText("Индекс корня");
    QPushButton *newANAndRootsButton = new QPushButton("Изменить", this);
    connect(newANAndRootsButton, &QPushButton::clicked, this, [this, newANInput, newRootIndexInput]() {
        QString anText = newANInput->text();
        QString indexText = newRootIndexInput->text();
        changeRootAndAN(anText, indexText);
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
    calculateValueAtXInput->setPlaceholderText("число X");
    QPushButton *calculateValueAtXButton = new QPushButton("Вычислить", this);
    connect(calculateValueAtXButton, &QPushButton::clicked, this, [this, calculateValueAtXInput]() {
        QString inputText = calculateValueAtXInput->text();
        calculateValueAtX(inputText);
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
    setNewPolynomialANInput->setMaximumWidth(60);
    QLineEdit *setNewPolynomialRootsInput = new QLineEdit(this);
    setNewPolynomialRootsInput->setPlaceholderText("корни (через пробел, пример: (1 -2) (3 5))");
    setNewPolynomialRootsInput->setMinimumWidth(250);
    QPushButton *setNewPolynomialButton = new QPushButton("Задать", this);

    // Создаем горизонтальный макет для метки и полей ввода
    QHBoxLayout *setNewPolynomialLayout = new QHBoxLayout();
    setNewPolynomialLayout->addWidget(setNewPolynomialLabel);
    setNewPolynomialLayout->addWidget(setNewPolynomialANInput);
    setNewPolynomialLayout->addWidget(setNewPolynomialRootsInput);
    setNewPolynomialLayout->addWidget(setNewPolynomialButton);
    mainLayout->addLayout(setNewPolynomialLayout);

    // Подключаем кнопку "Задать новый полином" к слоту
    connect(setNewPolynomialButton, &QPushButton::clicked, this, [this, setNewPolynomialANInput, setNewPolynomialRootsInput]() {
        QString anText = setNewPolynomialANInput->text();
        QString rootsText = setNewPolynomialRootsInput->text();
        setNewPolynomial(anText, rootsText);
    });

    // Добавляем кнопку "Выход"
    QPushButton *exitButton = new QPushButton("Выход", this);
    mainLayout->addWidget(exitButton);

    // Подключаем кнопку "Выход" к слоту
    connect(exitButton, &QPushButton::clicked, this, &TInterface::exitApplication);

    // Установка основного макета
    setLayout(mainLayout);
}

void TInterface::clearOutput() {
    outputField->clear(); // Очищаем поле вывода при нажатии на кнопку "Очистить"
}

void TInterface::exitApplication() {
    QApplication::quit();
}

TInterface::~TInterface()
{
    delete outputField;
    delete clearButton;
    delete outputLayout;
    delete mainLayout;

    delete canonicalFormLabel;
    delete canonicalFormButton;
    delete canonicalFormLayout;

    delete classicalFormLabel;
    delete classicalFormButton;
    delete classicalFormLayout;

    delete changeRootsCountLabel;
    delete changeRootsCountInput;
    delete changeRootsCountButton;
    delete changeRootsCountLayout;

    delete newANAndRootsLabel;
    delete newANInput;
    delete newRootIndexInput;
    delete newANAndRootsButton;
    delete newANAndRootsLayout;

    delete calculateValueAtXLabel;
    delete calculateValueAtXInput;
    delete calculateValueAtXButton;
    delete calculateValueAtXLayout;

    delete setNewPolynomialLabel;
    delete setNewPolynomialANInput;
    delete setNewPolynomialRootsInput;
    delete setNewPolynomialButton;
    delete setNewPolynomialLayout;

    delete exitButton;
}

void TInterface::showCanonicalForm()
{
    QString outputText;

    // polynom->setPrintMode(EPrintMode::EPrintModeCanonical);
    // outputText << *polynom;
    // TODO: вместо этого кидать запрос на сервер

    outputField->setText(outputText);
}

void TInterface::showClassicalForm()
{
    QString outputText;

    // polynom->setPrintMode(EPrintMode::EPrintModeClassic);
    // outputText << *polynom;
    // TODO: вместо этого кидать запрос на сервер

    outputField->setText(outputText);
}

void TInterface::changeRootsCount(QString& inputText)
{
    QString outputText; // Результирующая строка
    bool ok;
    int size = inputText.toInt(&ok);
    QString infoText;

    if (!ok || size <= 0)
    {
        QMessageBox::critical(this, "Ошибка", "Некорректный размер нового полинома");
        return;
    }

    // Создаем диалоговое окно для изменения размера массива
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Изменить количество корней");

    // Метка и readonly поле для старого полинома
    QLabel* oldRootLabel = new QLabel("Текущий полином (нумерация корней с нуля):", dialog);
    QLineEdit* oldRootField = new QLineEdit(dialog);

    // infoText << *polynom;
    // TODO: вместо этого кидать запрос на сервер

    oldRootField->setText(infoText);
    oldRootField->setReadOnly(true);

    int addedCount = 0; // size - polynom->getRootsCount() ; // меняем размер массива корней
    // TODO: вместо этого кидать запрос на сервер

    QString newRootLabelText = "Введите " + QString::number(addedCount) + " Новых корней (через пробел): "  ;
    QLabel* newRootLabel = new QLabel(newRootLabelText, dialog);
    QLineEdit* newRootInput = new QLineEdit(dialog);

    // Кнопка подтверждения
    QPushButton* confirmButton = new QPushButton("Подтвердить", dialog);
    connect(confirmButton, &QPushButton::clicked, dialog, &QDialog::accept);

    // Макет для диалогового окна
    QVBoxLayout* dialogLayout = new QVBoxLayout();
    dialogLayout->addWidget(oldRootLabel);
    dialogLayout->addWidget(oldRootField);
    dialogLayout->addWidget(newRootLabel);
    dialogLayout->addWidget(newRootInput);
    dialogLayout->addWidget(confirmButton);
    dialog->setLayout(dialogLayout);

    // если размер массива уменьшился
    if (addedCount < 0)
    {
        clearOutput();
        outputText.clear();
        // polynom->changeArrRootSize(size);
        // outputText << *polynom;
        // TODO: вместо этого кидать запрос на сервер
        outputField->setText(outputText);
        QMessageBox::information(this, "Успех", "Полином изменён успешно");
        return;
    }
    // если размер массива не изменился
    if (addedCount == 0)
    {
        QMessageBox::information(this, "Нет изменений", "Полином останется того же размера");
        return;
    }
    // Показываем диалоговое окно и ждем подтверждения
    if (dialog->exec() == QDialog::Accepted)
    {
        QStringList rootsList = newRootInput->text().split(' '); // Разделяем строку на части по пробелу
        if (rootsList.size() != addedCount * 2)
        {
            QMessageBox::critical(this, "Ошибка", "Количество введенных корней не соответсвует необходимому, полином не изменится");
            return;
        }

        QString arr[2];
        int iter = 0;

        for (QString& item : rootsList)
        {
            if (!item.isEmpty())
            { // Проверяем, что часть не пустая
                arr[iter++] = item;
            }

            if (iter == 2)
            {
                QString concaetedNum;
                // number tmpNum;
                // concaetedNum = arr[0] + " " + arr[1];
                // concaetedNum >> tmpNum;
                // TODO: вместо этого кидать запрос на сервер - чтобы он отвалидировал строку в тип number

                // polynom->changeArrRootSize(polynom->getRootsCount() + 1);
                // polynom->changeRootByIndex(polynom->getRootsCount() - 1, tmpNum);
                // polynom->calcCoefFromRoots();
                // TODO: вместо этого кидать запрос на сервер

                clearOutput();
                outputText.clear();
                // outputText << *polynom;
                // TODO: вместо этого кидать запрос на сервер
                outputField->setText(outputText);

                iter = 0;
            }

        }

        QMessageBox::information(this, "Успех", "Полином изменён успешно");

    }

    delete dialog;

}

void TInterface::changeRootAndAN(QString& anText, QString& indexText)
{
    QString outputText; // Результирующая строка

    if (anText.length() > 0)
    {
        // number numAN; // Введённые данные для a_n в числовом представлении
        // anText >> numAN;
        // TODO: вместо этого кидать запрос на сервер - чтобы он отвалидировал строку в тип number

        // polynom->setCanonicCoef(numAN);
        // polynom->calcCoefFromRoots();
        // TODO: вместо этого кидать запрос на сервер

        clearOutput();
        outputText.clear();
        // outputText << *polynom;
        // TODO: вместо этого кидать запрос на сервер

        outputField->setText(outputText);
    } else
    {
        QMessageBox::information(this, "Инфо", "Поля пустые, изменений нет");
        return;
    }

    bool ok;
    int index = indexText.toInt(&ok);
    QString infoText;

    if (!ok || index < 0)
    {
        QMessageBox::information(this, "Инфо", "Корни не переданы, изменен только a_n");
        return;
    }

    // Создаем диалоговое окно для изменения корня
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Изменить корень");

    // Метка и readonly поле для старого корня
    QLabel* oldRootLabel = new QLabel("Текущий полином (нумерация корней с нуля):", dialog);
    QLineEdit* oldRootField = new QLineEdit(dialog);

    // infoText << *polynom;
    // TODO: вместо этого кидать запрос на сервер

    oldRootField->setText(infoText);
    oldRootField->setReadOnly(true);

    // Поле ввода для нового корня
    QString newRootLabelText = "Новый корень по индексу " + QString::number(index) + ":";
    QLabel* newRootLabel = new QLabel(newRootLabelText, dialog);
    QLineEdit* newRootInput = new QLineEdit(dialog);

    // Кнопка подтверждения
    QPushButton* confirmButton = new QPushButton("Подтвердить", dialog);
    connect(confirmButton, &QPushButton::clicked, dialog, &QDialog::accept);

    // Макет для диалогового окна
    QVBoxLayout* dialogLayout = new QVBoxLayout();
    dialogLayout->addWidget(oldRootLabel);
    dialogLayout->addWidget(oldRootField);
    dialogLayout->addWidget(newRootLabel);
    dialogLayout->addWidget(newRootInput);
    dialogLayout->addWidget(confirmButton);
    dialog->setLayout(dialogLayout);

    // Показываем диалоговое окно и ждем подтверждения
    if (dialog->exec() == QDialog::Accepted)
    {
        QString rootText;

        // number newRoot;
        // rootText = newRootInput->text();
        // rootText >> newRoot;
        // TODO: вместо этого кидать запрос на сервер - чтобы он отвалидировал строку в тип number

        bool isChanged = false; // polynom->changeRootByIndex(index, newRoot);
        // polynom->calcCoefFromRoots();
        // TODO: вместо этого кидать запрос на сервер

        clearOutput();
        outputText.clear();
        // outputText << *polynom;
        // TODO: вместо этого кидать запрос на сервер
        outputField->setText(outputText);

        if (isChanged) {
            QMessageBox::information(this, "Успех", "Корень изменён успешно");
        } else {
            QMessageBox::critical(this, "Ошибка", "Корень не изменился, проверьте правильность ввода");
        }
    }

    delete dialog;

}

void TInterface::calculateValueAtX(QString& inputText)
{
    QString outputText;
    // number x;
    // inputText >> x;
    // TODO: вместо этого кидать запрос на сервер - чтобы он отвалидировал строку в тип number

    // number value = polynom->value(x);
    // TODO: вместо этого кидать запрос на сервер

    outputText += "P(";
    // outputText << x;
    outputText += ") = ";
    // outputText << value;

    outputField->setText(outputText);
}

void TInterface::setNewPolynomial(QString& anText, QString& rootsText)
{
    if (anText.length() > 0)
    {
        QString outputText; // Результирующая строка

        // number numAN; // Введённые данные для a_n в числовом представлении
        // anText >> numAN;
        // TODO: вместо этого кидать запрос на сервер - чтобы он отвалидировал строку в тип number

        // polynom->flushMemory();
        // polynom->setCanonicCoef(numAN);
        // TODO: вместо этого кидать запрос на сервер

        clearOutput();
        outputText.clear();
        // outputText << *polynom;
        // TODO: вместо этого кидать запрос на сервер
        outputField->setText(outputText);

        if (rootsText.length() == 0) return;

        QStringList rootsList = rootsText.split(' '); // Разделяем строку на части по пробелу
        QString arr[2] = {};
        int tmp = 0;

        for (QString& rootText : rootsList)
        {
            if (!rootText.isEmpty())
            { // Проверяем, что часть не пустая
                arr[tmp++] = rootText;
            }

            if (tmp == 2)
            {
                QString concaetedNum;
                // number tmpNum;
                // concaetedNum = arr[0] + " " + arr[1];
                // concaetedNum >> tmpNum;
                // TODO: вместо этого кидать запрос на сервер - чтобы он отвалидировал строку в тип number

                // polynom->addRoot(tmpNum);
                // polynom->calcCoefFromRoots();
                // TODO: вместо этого кидать запрос на сервер

                clearOutput();
                outputText.clear();
                // outputText << *polynom;
                // TODO: вместо этого кидать запрос на сервер
                outputField->setText(outputText);

                tmp = 0;
            }

        }

        // formRequest(SET_NEW_POLYNOMIAL_REQUEST, data); // ПРИМЕР: Отправляем запрос на задание нового полинома с параметром data.
    }
    else
    {
        outputField->setText("Поле ввода пустое!");
    }
}


void TInterface::formRequest(RequestType requestType, const QString& params)
{
    emit request(QString::number(requestType) + (params.isEmpty() ? "" : " " + params));
    // Эмитируем сигнал запроса для отправки на сервер.
}

void TInterface::answer(const QString& response)
{
    // Разделяем ответ на тип и данные
    QStringList parts = response.split(" ");
    if (parts.isEmpty()) {
        outputField->setText("Ошибка: пустой ответ.");
        return;
    }

    // Извлекаем тип ответа
    bool ok;
    int responseType = parts[0].toInt(&ok);
    if (!ok) {
        outputField->setText("Ошибка: неверный формат ответа.");
        return;
    }

    // Обработка ответа в зависимости от типа
    switch (responseType)
    {
    case CANONICAL_FORM_ANSWER:
        if (parts.size() > 1) {
            QString polynomData = parts.mid(1).join(" "); // Объединяем оставшиеся части как данные полинома
            outputField->setText("Каноническая форма: " + polynomData);
        } else {
            outputField->setText("Ошибка: недостаточно данных для канонической формы.");
        }
        break;

    case CLASSICAL_FORM_ANSWER:
        if (parts.size() > 1) {
            QString polynomData = parts.mid(1).join(" ");
            outputField->setText("Классическая форма: " + polynomData);
        } else {
            outputField->setText("Ошибка: недостаточно данных для классической формы.");
        }
        break;

    case CHANGE_ROOTS_COUNT_ANSWER:
        outputField->setText("Количество корней изменено.");
        break;

    case CHANGE_ROOT_AND_AN_ANSWER:
        outputField->setText("Изменение a_n и корня выполнено.");
        break;

    case CALCULATE_VALUE_AT_X_ANSWER:
        if (parts.size() > 2) {
            QString xValue = parts[1];
            QString resultValue = parts[2];
            outputField->setText("Значение в точке " + xValue + ": " + resultValue);
        } else {
            outputField->setText("Ошибка: недостаточно данных для вычисления значения.");
        }
        break;

    case SET_NEW_POLYNOMIAL_ANSWER:
        outputField->setText("Новый полином установлен.");
        break;

    case ERROR_UNKNOWN_REQUEST:
        outputField->setText("Ошибка: неизвестный запрос.");
        break;

    default:
        outputField->setText("Ошибка: неверный тип ответа.");
        break;
    }
}

