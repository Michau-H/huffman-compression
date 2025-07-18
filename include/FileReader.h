#ifndef FileReader_H
#define FileReader_H
#include <vector>
#include <string>
#include "Symbol.h"

class FileReader {
public:
    FileReader() = default;

    std::vector<Symbol> analyzeFile(const std::string&);
};
#endif