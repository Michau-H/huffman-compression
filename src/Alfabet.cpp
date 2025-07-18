#include "Alfabet.h"

Alfabet::Alfabet(const std::vector<Symbol>& in) : allSymbols(in) {}

void Alfabet::sortAlfabet() {
    std::sort(allSymbols.begin(), allSymbols.end(),
              [](const Symbol& a, const Symbol& b) {
                  return a.get_f() < b.get_f();
              });
}

const std::vector<Symbol>& Alfabet::getAlfabet() const {
    return allSymbols;
}

void Alfabet::printAlfabet() const {
    for (const auto& s : allSymbols) {
        char c = s.get_s();
        std::cout << std::setw(6) << static_cast<int>(static_cast<unsigned char>(c)) << " (";
        if (c == '\n')
            std::cout << "\\n";
        else if (c == '\r')
            std::cout << "\\r";
        else if (c == '\t')
            std::cout << "\\t";
        else if (c == ' ')
            std::cout << " ";
        else if (std::isprint(static_cast<unsigned char>(c)))
            std::cout << c;
        else
            std::cout << "?";
        std::cout << ")  : " << s.get_f() << '\n';
    }
}

double Alfabet::idealCodeLen() const{
    double totF=0;
    for(auto&s : allSymbols){
        totF += s.get_f();
    }

    double H=0.0;
    for(auto&s : allSymbols){
        double p = s.get_f() /totF;
        if(p>0.0)
            H -= p*std::log2(p);
    }
    return H;
}