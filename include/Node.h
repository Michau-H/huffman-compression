#ifndef Node_H
#define Node_H
#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include "Symbol.h"

class Node {
    Symbol s;
    bool bit;
    Node* parent;
    Node* left;
    Node* right;
    std::string code;

    public:
        Node(Symbol);
        Symbol getSymbol();
        void setParent(Node*);
        void setLeft(Node*);
        void setRight(Node*);
        void setBit(bool);
        void addBit(bool);

        void setCode(const std::string&);
        const std::string& getCode() const;

        Node* getParent() const;
        Node* getLeft() const;
        Node* getRight() const;

        void printNode();
};
#endif