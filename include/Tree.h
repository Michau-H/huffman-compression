#ifndef Tree_H
#define Tree_H

#include <vector>
#include <string>
#include <cstdint>
#include "Symbol.h"
#include "Node.h"
#include "Alfabet.h"
#include "BitWriter.h"
#include "BitReader.h"

class Tree {
    std::vector<Node*> tree;
    Node* root = nullptr;

    uint32_t countTreeBits(Node*) const;
    void writeTree(Node*, BitWriter&);
    void assignCodes(Node*, const std::string&);
    Node* readTree(BitReader& r);

public:
    Tree(const Alfabet&);
    ~Tree();

    void genTree();
    void printCodes();
    void compressFile(const std::string& inTxt, const std::string& outBin);
    void decompressFile(const std::string& inBin, const std::string& outTxt);
    double avgCodeLen() const;
};

#endif
