#ifndef Alfabet_H
#define Alfabet_H
#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include "Symbol.h"

class Alfabet {
private:
    std::vector<Symbol> allSymbols;

public:
    Alfabet() = default;
    Alfabet(const std::vector<Symbol>&);

    void sortAlfabet();

    const std::vector<Symbol>& getAlfabet() const;
    void printAlfabet() const;
    double idealCodeLen() const;
};

#endif