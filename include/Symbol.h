#ifndef Symbol_H
#define Symbol_H
#include <vector>
#include <iomanip>
#include <iostream>

class Symbol {
    char s;
    int f;

    public:
        Symbol() = default;
        Symbol(char);
        Symbol(char, int);
        void print_s();
        void add_f();
        char get_s() const;
        int get_f() const;
};
#endif