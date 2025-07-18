#include "BitReader.h"
#include <stdexcept>

BitReader::BitReader(std::istream& input)
  : in(input), buffer(0), pos(8)
{}

bool BitReader::readBit() {
    if (pos == 8) {
        char c;
        if (!in.get(c)) {
            throw std::runtime_error("BitReader: EOF while reading bit");
        }
        buffer = static_cast<uint8_t>(c);
        pos = 0;
    }
    bool bit = (buffer & (1 << (7 - pos))) != 0;
    ++pos;
    return bit;
}

uint8_t BitReader::readByte() {
    uint8_t byte = 0;
    for (int i = 0; i < 8; ++i) {
        byte = static_cast<uint8_t>((byte << 1) | (readBit() ? 1 : 0));
    }
    return byte;
}

//odczytywanie dlugosci 
uint32_t BitReader::readUInt32() {
    uint32_t value = 0;
    for (int i = 0; i < 4; ++i) {
        char c;
        if (!in.get(c)) {
            throw std::runtime_error("BitReader: EOF while reading uint32");
        }
        value = (value << 8) | static_cast<uint8_t>(c);
    }
    return value;
}
