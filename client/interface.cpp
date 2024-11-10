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

    tempOutputField = outputField;
    tempInputField = nullptr;

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
        sendChangeRootAndANRequest(anText, indexText);
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
        sendSetNewPolynomialRequest(anText, rootsText);
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

    // strPolynom используется для сохранения текущего состояния полинома, очищаем её
    clearStrPolynom();

    qDebug() << "Супер-важно! теперь мы обязаны передавать параметры запроса в таком порядке:\n"
                "код_запроса;полином;всё_остальное;итд\n"
                "Полином из strPolynom автоматически встраивается в запрос, если юзать метод formRequest, передавать руками его не нужно\n";
    qDebug() << "А ответ от сервера приходит в формате: код_запроса;статус;данные\n";
}

TInterface::~TInterface()
{
    delete tempOutputField;
    delete tempInputField;

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

void TInterface::clearStrPolynom() {
    strPolynom = "P(x) = (1+0i)";
}

void TInterface::sendCanonicalFormRequest()
{
    tempOutputField = outputField;
    formRequest(CANONICAL_FORM_REQUEST); // Отправляем запрос на вывод канонического вида
}

void TInterface::sendClassicalFormRequest()
{
    tempOutputField = outputField;
    formRequest(CLASSICAL_FORM_REQUEST); // Отправляем запрос на вывод классического вида
}

void TInterface::sendChangeRootsCountRequest(const QString& count)
{
    QString outputText; // Результирующая строка
    bool ok;
    int size = count.toInt(&ok);
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

void TInterface::sendChangeRootAndANRequest(QString& anText, QString& indexText)
{
    if (anText.length() > 0)
    {
        formRequest(SET_CANONIC_COEF_REQUEST, anText);
    }

    bool ok;
    int index = indexText.toInt(&ok);

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


    oldRootField->setText(strPolynom);
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
        QString reqText = QString::number(index) + separator + newRootInput->text();
        formRequest(CHANGE_ROOT_REQUEST, reqText);

        // if (isChanged) {
        //     QMessageBox::information(this, "Успех", "Корень изменён успешно");
        // } else {
        //     QMessageBox::critical(this, "Ошибка", "Корень не изменился, проверьте правильность ввода");
        // }
    }

    delete dialog;
}

void TInterface::sendCalculateValueAtXRequest(const QString& x)
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

void TInterface::sendSetNewPolynomialRequest(QString& anText, QString& rootsText)
{
    clearStrPolynom(); // Сброс текущего состояния полинома

    if (anText.length() == 0 && rootsText.length() == 0)
    {
        QMessageBox::information(this, "Инфо", "Поля пустые, полином сброшен");
        clearOutput();
        return;
    }

    if (anText.length() > 0 && rootsText.length() > 0)
    {
        formRequest(SET_NEW_POLYNOMIAL_REQUEST, anText + separator + rootsText);
        return;
    }

    if (anText.length() > 0) {
        formRequest(SET_CANONIC_COEF_REQUEST, anText);
    }

    if (rootsText.length() > 0)
    {
        formRequest(ADD_ROOTS_REQUEST, rootsText);
    }
}

void TInterface::formRequest(RequestType requestType, const QString& params)
{
    emit request(QString::number(requestType) + separator + strPolynom + separator + params);
    // Эмитируем сигнал запроса для отправки на сервер.
}

void TInterface::answer(const QString& response)
{

    char separatorChar = separator.toLatin1(); // Преобразование QChar в char
    int pos = response.indexOf(separatorChar); // Используем response для поиска сепаратора

    // Проверка на наличие разделителя
    if (pos == -1) {
        qDebug() << "Separator not found in message.";
        return;
    }

    int requestType = response.left(pos).toInt(); // Получаем тип запроса
    QString strMsg = response.mid(pos + 1); // Убираем тип запроса из сообщения

    const QString statusCode = strMsg.mid(0, strMsg.indexOf(separatorChar)); // Получаем статус код из запроса
    strMsg = strMsg.remove(0, strMsg.indexOf(separatorChar) + 1); // Убираем статус код из запроса

    switch (requestType) {
    case CANONICAL_FORM_ANSWER:
        // strPolynom = strMsg; // Здесь не присваиваем, тк полином хранится в классическом виде
        tempOutputField->setText(strMsg);
        break;
    case CLASSICAL_FORM_ANSWER:
        strPolynom = strMsg; // Остальная часть ответа - полином (на данный момент)
        tempOutputField->setText(strPolynom);
        break;
    case SET_CANONIC_COEF_ANSWER:
        if (statusCode == "ERR")
        {
            tempOutputField->setText("error in SET_CANONIC_COEF_ANSWER");
            break;
        }

        strPolynom = strMsg; // Остальная часть ответа - полином (на данный момент)
        tempOutputField->setText(strPolynom);
        break;
    case SET_NEW_POLYNOMIAL_ANSWER:
    {
        strPolynom = strMsg; // Остальная часть ответа - полином (на данный момент)
        tempOutputField->setText(strPolynom);
        break;
    }
    case CHANGE_ROOT_ANSWER:
        if (statusCode == "ERR")
        {
            tempOutputField->setText("error in CHANGE_ROOT_ANSWER");
            QMessageBox::critical(this, "Ошибка", "Корень не изменился, проверьте правильность ввода"); // Костыляем, по другому не умею
            break;
        }

        strPolynom = strMsg; // Остальная часть ответа - полином (на данный момент)
        tempOutputField->setText(strPolynom);
        QMessageBox::information(this, "Успех", "Корень изменён успешно");  // Костыляем, по другому не умею
        break;
    case ADD_ROOTS_ANSWER:
    {
        strPolynom = strMsg; // Остальная часть ответа - полином (на данный момент)
        tempOutputField->setText(strPolynom);
        break;
    }
    default:
        tempOutputField->setText("Неизвестный ответ.");
        break;
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
