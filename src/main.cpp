#include <iostream>
#include <string>
#include <vector>

#include "FileReader.h"
#include "Alfabet.h"
#include "Tree.h"
#include "Symbol.h"
#include "Node.h"
#include "BitWriter.h"
#include "BitReader.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage:\n"
                  << "  " << argv[0] << " c <input.txt>    # compress\n"
                  << "  " << argv[0] << " d <input.bin>    # decompress\n";
        return 1;
    }

    char mode = argv[1][0];
    std::string inputPath = argv[2];
    std::string outputPath;

    try {
        if (mode == 'c') {
            auto pos = inputPath.rfind('.');
            if (pos != std::string::npos)
                outputPath = inputPath.substr(0, pos) + "_c.bin";
            else
                outputPath = inputPath + "_c.bin";

            FileReader fr;
            std::vector<Symbol> symbols = fr.analyzeFile(inputPath);
            Alfabet alfabet(symbols);
            alfabet.sortAlfabet();

            Tree huffman(alfabet);
            huffman.genTree();
            huffman.compressFile(inputPath, outputPath);

            std::cout << "Compressed '" << inputPath
                      << "' -> '" << outputPath << "'\n";
            std::cout << "|| avg code len: " << huffman.avgCodeLen()
                      << "  ||  ideal code len: " << alfabet.idealCodeLen() << "||\n"; 
        }

        else if (mode == 'd') {
            auto pos = inputPath.rfind('.');
            if (pos != std::string::npos)
                outputPath = inputPath.substr(0, pos) + "_d.txt";
            else
                outputPath = inputPath + "_d.txt";

            std::vector<Symbol> empty;
            Alfabet eempty(empty);
            Tree huffman(eempty);
            huffman.decompressFile(inputPath, outputPath);

            std::cout << "Decompressed '" << inputPath
                      << "' -> '" << outputPath << "'\n";
        }
        else {
            std::cerr << "Unknown mode '" << mode << "'; use 'c' for compression or 'd' for decompression.\n";
            return 1;
        }

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
