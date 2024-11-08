#include "polynom.h"
#include <iostream>
#include <array.h>
#include <math.h>
#include "QString"

using namespace std;


TPolynom::TPolynom(number canonicCoef) {
    this->canonicCoef = canonicCoef;
    this->printMode = EPrintMode::EPrintModeClassic;
    this->arrCoef = new TArray();
    this->arrRoot = new TArray();
}

TPolynom::~TPolynom() {
    this->flushMemory();
}

unsigned TPolynom::getRootsCount() {
    return this->arrRoot->getSize();
}

void TPolynom::addCoef(number coef) {
    this->arrCoef->appendElement(coef);
}

void TPolynom::addRoot(number root) {
    this->arrRoot->appendElement(root);
}


number TPolynom::value (number val) {
    number result = 0;
    for (unsigned i = 0; i < this->arrCoef->getSize(); i++) {
        int rootPow = (this->arrCoef->getSize() - i - 1);
        result += this->arrCoef->get(i) * pow(val, rootPow);
    }

    return result;
}

ostream& operator<<(ostream& os, TPolynom& polynom) {
    cout << "P(x) = ";

    if (!polynom.arrRoot->getSize()) {
        cout << polynom.canonicCoef;
        return os;
    }

    if (polynom.printMode == EPrintMode::EPrintModeCanonical) {
        for (unsigned i = 0; i < polynom.arrCoef->getSize() - 1; i++) {
            int pow = (polynom.arrCoef->getSize() - i - 1);
            os << polynom.arrCoef->get(i);
            if (pow != 0) os << "x";
            if (pow > 1) os << "^" << pow;
            os << " + ";
        }
        cout << polynom.arrCoef->get(polynom.arrCoef->getSize() - 1);

    } else {
        cout << polynom.canonicCoef;
        for (unsigned i = 0; i < polynom.arrRoot->getSize(); ++i)
        {
            cout << "(x - "  << polynom.arrRoot->get(i) << ")";
        }

    }

    os << "\n";

    return os;
}

QString& operator<<(QString& s, TPolynom& polynom) {
    s += "P(x) = ";

    if (!polynom.arrRoot->getSize()) {
        s << polynom.canonicCoef;
        return s;
    }

    if (polynom.printMode == EPrintMode::EPrintModeCanonical) {
        for (unsigned i = 0; i < polynom.arrCoef->getSize() - 1; i++) {
            int pow = (polynom.arrCoef->getSize() - i - 1);
            s << polynom.arrCoef->get(i);
            if (pow != 0) s += "x";
            if (pow > 1) {
                s += "^";
                s += QString().setNum(pow);
            }
            s += " + ";
        }
        s << polynom.arrCoef->get(polynom.arrCoef->getSize() - 1);

    } else {
        s << polynom.canonicCoef;
        for (unsigned i = 0; i < polynom.arrRoot->getSize(); ++i)
        {
            s += "(x - ";
            s << polynom.arrRoot->get(i);
            s += ")";
        }

    }

    // s += " "; // проверить - нужен ли

    return s;
}

void TPolynom::flushMemory() {
    this->arrCoef->flushMemory();
    this->arrRoot->flushMemory();
}

void TPolynom::setPrintMode(EPrintMode mode) {
    this->printMode = mode;
}

void TPolynom::setCanonicCoef(number coef) {
    this->canonicCoef = coef;
}

void TPolynom::calcCoefFromRoots() {
    TArray classicalCoeffs; // Начинаем с единичного полинома
    classicalCoeffs.appendElement(1); // Начальный коэффициент для x^0

    for (unsigned i = 0; i < this->arrRoot->getSize(); i++) {
        TArray newCoeffs;
        newCoeffs.fillArray(classicalCoeffs.getSize() + 1);

        for (unsigned j = 0; j < classicalCoeffs.getSize(); j++) {
            newCoeffs.replaceElement(j, newCoeffs.get(j) + classicalCoeffs.get(j)); // Сохраняем старые коэффициенты
            newCoeffs.replaceElement(j + 1, newCoeffs.get(j + 1) + (-this->arrRoot->get(i) * classicalCoeffs.get(j)) ); // Умножаем на (x - root)
        }

        classicalCoeffs.fillArray(newCoeffs.getSize());
        for (unsigned t = 0; t < newCoeffs.getSize(); t++) { // Обновляем коэффициенты
            classicalCoeffs.replaceElement(t, newCoeffs.get(t));
        }
    }

    // Умножаем на канонический коэффициент
    for (int i = 0; i < (int)classicalCoeffs.getSize(); i++) {
        classicalCoeffs.replaceElement(i, classicalCoeffs.get(i) * this->canonicCoef);
    }

    // Сохраняем классические коэффициенты
    this->arrCoef->flushMemory();
    for (int i = 0; i < (int)classicalCoeffs.getSize(); i++) {
        this->arrCoef->appendElement(classicalCoeffs.get(i));
    }

}

int TPolynom::changeArrRootSize(unsigned newSize) {
    int addedCount = newSize - this->arrRoot->getSize();

    this->arrRoot->resizeArray(newSize);
    this->calcCoefFromRoots();

    return addedCount;
}

bool TPolynom::changeRootByIndex(unsigned index, number newRoot)
{
    return arrRoot->replaceElement(index, newRoot);
}

void TPolynom::printRoots()
{
    arrRoot->print();
}

number TPolynom::getCanonicCoef()
{
    return canonicCoef;
}
