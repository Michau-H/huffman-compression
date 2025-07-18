#ifndef BITREADER_H
#define BITREADER_H

#include <istream>
#include <cstdint>

class BitReader {
    std::istream& in;
    uint8_t       buffer;
    int           pos;

public:
    explicit BitReader(std::istream& input);
    ~BitReader() = default;

    bool readBit();
    uint8_t readByte();
    uint32_t readUInt32();
};

#endif
