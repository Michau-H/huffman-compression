#include "FileReader.h"
#include <fstream>
#include <stdexcept>

std::vector<Symbol> FileReader::analyzeFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Can not open file: " + path);
    }

    std::vector<Symbol> statystyki;

    char character;
    while (file.get(character)) {
        bool exist = false;
        for (auto& s : statystyki) {
            if (s.get_s() == character) {
                s.add_f();
                exist = true;
                break;
            }
        }

        if (!exist) {
            statystyki.emplace_back(character);

        }
    }

    return statystyki;
}
