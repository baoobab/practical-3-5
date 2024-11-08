#include "array.h"
#include "number.h"
#include <cmath>
#include <iostream>

using namespace std;


TArray::TArray() {
    this->size = 0;
    this->arr = 0;
}

TArray::~TArray() {
    this->flushMemory();
}

unsigned TArray::getSize() {
    return this->size;
}

bool TArray::checkIndex(unsigned int index) {
    return (index < this->size);
}

void TArray::flushMemory() {
    delete[] this->arr;
    this->size = 0;
    this->arr = 0;
}

void TArray::fillArray(unsigned newSize, number el) {
    number* newArr = new number[newSize];

    for (number* curr = newArr; curr != (newArr + newSize); curr++) {
        *curr = el;
    }
    delete[] this->arr;

    this->arr = newArr;
    this->size = newSize;
}

void TArray::appendElement(number el) {
    number* newArr = new number[this->size + 1];
    unsigned cnt = 0;

    for (number* curr = this->arr; curr != (this->arr + this->size); curr++) {
        *(newArr + cnt++) = *curr;
    }
    *(newArr + cnt) = el;

    delete[] this->arr;

    this->arr = newArr;
    this->size++;
}

void TArray::removeElementByIndex(unsigned index) {
    if (!checkIndex(index) || !this->size) return; // Если такого индекса нет, или массив пустой - выходим

    number* newArr = new number[this->size - 1];
    unsigned cnt = 0;
    for (number* curr = this->arr; curr != (this->arr + this->size); curr++) {
        if (index-- == 0) continue; // скипаем удаляемый элемент
        *(newArr + cnt++) = *curr;
    }

    delete[] this->arr;

    this->arr = newArr;
    this->size--;
}

void TArray::print() {
    if (!this->size) {
        cout << "Array is empty" << "\n";
        return;
    }
    cout << "Array (size is " << this->size << "): ";
    for (number* curr = this->arr; curr != (this->arr + this->size); curr++) {
        cout << *curr << " ";
    }
    cout << "\n";
}

number TArray::mediumValue() {
    if (!this->size) return 0;

    number summ = 0;
    for (number* curr = this->arr; curr != (this->arr + this->size); curr++) {
        summ += *curr;
    }
    return summ/this->size;

}

number TArray::standardDeviation() {
    if (!this->size || this->size == 1) return 0;

    number mediumValue = this->mediumValue();
    number standardSumm = 0;

    for (number* curr = this->arr; curr != (this->arr + this->size); curr++) {
        standardSumm += pow(*curr - mediumValue, 2);
    }

    return sqrt(standardSumm / (this->size - 1));
}

void TArray::quickSortHelper(int low, int high) {
    if (this->size <= 1) return;

    int i = low;
    int j = high;
    number pivot = *(this->arr+((i + j) / 2));
    number temp;

    while (i <= j) {
        while (*(this->arr+i) < pivot)
            i++;
        while (*(this->arr+j) > pivot)
            j--;
        if (i <= j) {
            temp = *(this->arr+i);
            *(this->arr+i) = *(this->arr+j);
            *(this->arr+j) = temp;
            i++;
            j--;
        }
    }
    if (j > low)
        this->quickSortHelper(low, j);
    if (i < high)
        this->quickSortHelper(i, high);
}

void TArray::quickSortReverseHelper(int low, int high) {
    if (this->size <= 1) return;

    int i = low;
    int j = high;
    number pivot = *(this->arr + ((i + j) / 2));
    number temp;

    while (i <= j) {
        while (*(this->arr + i) > pivot)
            i++;
        while (*(this->arr + j) < pivot)
            j--;
        if (i <= j) {
            temp = *(this->arr + i);
            *(this->arr + i) = *(this->arr + j);
            *(this->arr + j) = temp;
            i++;
            j--;
        }
    }

    if (j > low)
        this->quickSortReverseHelper(low, j);
    if (i < high)
        this->quickSortReverseHelper(i, high);
}

void TArray::sort() {
    this->quickSortHelper(0, this->size - 1);
}

void TArray::reverseSort() {
    this->quickSortReverseHelper(0, this->size - 1);
}

bool TArray::replaceElement(unsigned int index, number value) {
    if (!checkIndex(index)) {
        cout << "\nIndex out of range\n";
        return false;
    }

    *(this->arr + index) = value;
    return true;
}

void TArray::resizeArray(unsigned int newSize) {
    int elementsToAppend = newSize - this->size;

    if (elementsToAppend < 0) {
        while (elementsToAppend++) {
            this->removeElementByIndex(this->size - 1);
        }
    } else if (elementsToAppend > 0) {
        while (elementsToAppend--) {
            this->appendElement(0);
        }
    }

    cout << "Current dimension is: " << newSize << "\n";
    return;
}

number TArray::get(unsigned index) {
    if (!checkIndex(index)) {
        throw out_of_range("out");
    }

    return *(this->arr + index);
}
