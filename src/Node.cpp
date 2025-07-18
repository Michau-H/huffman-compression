#include "Node.h"

Node::Node(Symbol s2){
    s = s2;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    bit = false;
    code = "";
}

Symbol Node::getSymbol(){
    return s;
}

void Node::setParent(Node* p){
    parent = p;
}

void Node::setLeft(Node* p){
    left = p;
}

void Node::setRight(Node* p){
    right = p;
}

void Node::setBit(bool b){
    bit = b;
}

void Node::addBit(bool b){
    code += std::to_string(b);
}

void Node::setCode(const std::string& c){
    code = c;
}

const std::string& Node::getCode() const { 
    return code;
}

Node* Node::getLeft() const{
    return left;
}

Node* Node::getRight() const{
    return right;
}

Node* Node::getParent() const{
    return parent;
}

void Node::printNode() {
    std::cout << std::setw(15) << getCode() << " ";
    s.print_s();
}

