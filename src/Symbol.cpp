#include "Symbol.h"

Symbol::Symbol(char s2){
    s = s2;
    f = 1;
}

Symbol::Symbol(char s2, int f2){
    s = s2;
    f = f2;
}

void Symbol::print_s(){
    std::cout<< s << std::setw(6) << f << std::endl;
}

void Symbol::add_f(){
    f ++;
}

char Symbol::get_s() const{
    return s;
}

int Symbol::get_f() const{
    return f;
}
