#ifndef BITWRITER_H
#define BITWRITER_H

#include <ostream>
#include <cstdint>

class BitWriter {
    std::ostream& out;
    uint8_t       buffer = 0;
    int           pos    = 0;  // od 0 do 7

public:
    explicit BitWriter(std::ostream& o);
    ~BitWriter();

    void writeBit(bool b);
    void writeByte(uint8_t byte);
    void flush();
};

#endif
