#ifndef POLYNOM_H
#define POLYNOM_H

#include <number.h>
#include <array.h>
#include "QString"

enum EPrintMode {
    EPrintModeClassic,
    EPrintModeCanonical
};

class TPolynom {
private:
    EPrintMode printMode;

    number canonicCoef;
    TArray* arrCoef;
    TArray* arrRoot;
public:
    TPolynom(number canonicCoef = 1);
    ~TPolynom();
    void addCoef(number coef);
    void addRoot(number root);
    void flushMemory();
    void setPrintMode(EPrintMode mode);
    void setCanonicCoef(number coef);
    unsigned getRootsCount();
    number value(number val);
    friend ostream& operator<<(ostream&, TPolynom&);
    friend QString& operator<<(QString&, TPolynom&);
    void calcCoefFromRoots();
    int changeArrRootSize(unsigned newSize); // Возврщает int - кол-во добавленных эл-тов
    bool changeRootByIndex(unsigned index, number newRoot);
    void printRoots();
    number getCanonicCoef();
};

#endif // POLYNOM_H
