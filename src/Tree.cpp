#include "Tree.h"
#include <queue>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <unordered_map>

Tree::Tree(const Alfabet& alfabet) {
    for (auto& s : alfabet.getAlfabet())
        tree.push_back(new Node(s));
}

Tree::~Tree() {
    for (auto* n : tree)
        delete n;
}



// generowanie drzewa binarnego
void Tree::genTree() {
    auto cmp = [](Node* a, Node* b){
        return a->getSymbol().get_f() > b->getSymbol().get_f();
    };
    std::priority_queue<Node*,std::vector<Node*>,decltype(cmp)> pq(cmp);
    for (auto* n : tree) pq.push(n);

    while (pq.size()>1) {
        Node* l = pq.top(); pq.pop();
        Node* r = pq.top(); pq.pop();
        Symbol merged('*', l->getSymbol().get_f()+r->getSymbol().get_f());
        Node* p = new Node(merged);
        p->setLeft(l);  l->setParent(p);
        p->setRight(r); r->setParent(p);
        pq.push(p);
        tree.push_back(p);
    }
    root = pq.top();
    assignCodes(root, "");
}


// rekurecyjne wpisywanie kodow
void Tree::assignCodes(Node* n, const std::string& pre) {
    if (!n) return;
    n->setCode(pre);
    if (n->getLeft() || n->getRight()) {
        assignCodes(n->getLeft(),  pre + '0');
        assignCodes(n->getRight(), pre + '1');
    }
}


// wczytujemy drzewo
Node* Tree::readTree(BitReader& r) {
    bool flag = r.readBit();
    if (!flag) {
        Node* left  = readTree(r);
        Node* right = readTree(r);
        Symbol s('*', left->getSymbol().get_f() + right->getSymbol().get_f());
        Node* p = new Node(s);
        p->setLeft(left);   left->setParent(p);
        p->setRight(right); right->setParent(p);
        tree.push_back(p);
        return p;
    } else {
        uint8_t ch = r.readByte();
        Symbol s(static_cast<char>(ch), 0);
        Node* leaf = new Node(s);
        tree.push_back(leaf);
        return leaf;
    }
}



void Tree::printCodes() {
    std::vector<Node*> leaves;
    for (auto* n: tree)
        if (!n->getLeft() && !n->getRight())
            leaves.push_back(n);

    std::sort(leaves.begin(), leaves.end(),
              [](Node* a, Node* b){
                  return a->getSymbol().get_s() < b->getSymbol().get_s();
              });

    std::cout<<"Huffman codes:\n";
    for (auto* n: leaves) {
        char c = n->getSymbol().get_s();
        std::string esc = (c==' '?"space":
                          (c=='\n'?"\\n":
                          (c=='\t'?"\\t":std::string(1,c))));
        std::cout<<std::setw(6)<<esc<<" : "<<n->getCode()<<"\n";
    }
}





// dlugosc drzewa binarnego do wpisania na początku pliku .bin
uint32_t Tree::countTreeBits(Node* n) const {
    if (!n) return 0;
    uint32_t bits = 1;
    if (!n->getLeft() && !n->getRight()) bits += 8;
    else {
        bits += countTreeBits(n->getLeft());
        bits += countTreeBits(n->getRight());
    }
    return bits;
}




// zapisywanie drzewa do pliku .bin
void Tree::writeTree(Node* n, BitWriter& w) {
    if (!n) return;

    // jesli wezel to wpisuje 0
    if (n->getLeft()||n->getRight()) {
        w.writeBit(0);
        writeTree(n->getLeft(),  w);
        writeTree(n->getRight(), w);
    } 
    // jesli lisc to wpisuje 1 a nastpenie kod 8bitowy
    else {
        w.writeBit(1);
        w.writeByte(static_cast<uint8_t>(n->getSymbol().get_s()));
    }
}





// kompresowanie do pliku .bin
void Tree::compressFile(const std::string& inputPath,
                        const std::string& outputPath) {
    if (!root) throw std::runtime_error("Call genTree() first");

    std::ifstream fin(inputPath, std::ios::binary);
    if (!fin) throw std::runtime_error("Cannot open input: " + inputPath);
    std::ofstream fout(outputPath, std::ios::binary);
    if (!fout) throw std::runtime_error("Cannot open output: " + outputPath);

    //wpisywanie dlugosci na poczatek
    uint32_t treeBits = countTreeBits(root);
    fout.put(char((treeBits>>24)&0xFF));
    fout.put(char((treeBits>>16)&0xFF));
    fout.put(char((treeBits>>8 )&0xFF));
    fout.put(char((treeBits    )&0xFF));

    // wpisywanie drzewa binarnego
    BitWriter writer(fout);
    writeTree(root, writer);

    // tworzenie unordered_map znak + kod
    std::unordered_map<char,std::string> codeMap;
    for (auto* n: tree) {
        if (!n->getLeft() && !n->getRight()) {
            codeMap[n->getSymbol().get_s()] = n->getCode();
        }
    }

    // wpisywanie zakodowanego tekstu
    char c;
    while (fin.get(c)) {
        const auto& code = codeMap[c];
        for (char bit : code)
            writer.writeBit(bit=='1');
    }

    fin.close();
    fout.close();
}



void Tree::decompressFile(const std::string& inBin,
                          const std::string& outTxt) {
    std::ifstream fin(inBin, std::ios::binary);
    if (!fin) throw std::runtime_error("Cannot open input: " + inBin);
    BitReader reader(fin);

    // czytanie dlugosci 
    uint32_t treeBits = reader.readUInt32();

    // tworzenie nowego drzewa
    for (auto* n: tree) delete n;
    tree.clear();

    root = readTree(reader);
    assignCodes(root, ""); // nadajemy kody

    // wpisujemy do pliku wynikowego
    std::ofstream fout(outTxt, std::ios::binary);
        if (!fout) throw std::runtime_error("Cannot open output: " + outTxt);

    Node* curr = root;
    try {
        while (true) {
            bool b = reader.readBit();
            curr = b ? curr->getRight() : curr->getLeft();
            if (!curr->getLeft() && !curr->getRight()) {
                fout.put(curr->getSymbol().get_s());
                curr = root;
            }
        }
    }
    catch (std::runtime_error&) {//EOF
    }

    fin.close();
    fout.close();
}

double Tree::avgCodeLen() const{
    uint64_t totF = 0;
    uint64_t totB = 0;
    for(auto* n: tree){
        if(!n->getLeft() && !n->getRight()){
            totF += n->getSymbol().get_f();
            totB += n->getSymbol().get_f() * n->getCode().length();
        }
    }
    if(totF ==0) return 0.0;
    return static_cast<double>(totB) /totF;
}
