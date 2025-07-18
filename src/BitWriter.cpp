#include "BitWriter.h"

BitWriter::BitWriter(std::ostream& o)
  : out(o), buffer(0), pos(0) {}

BitWriter::~BitWriter() {
    flush();
}

void BitWriter::writeBit(bool b) {
    buffer |= (static_cast<uint8_t>(b) << (7 - pos));
    if (++pos == 8) {
        flush();
    }
}

void BitWriter::writeByte(uint8_t byte) {
    for (int i = 7; i >= 0; --i) {
        writeBit((byte >> i) & 1);
    }
}

void BitWriter::flush() {
    if (pos == 0) return;
    out.put(static_cast<char>(buffer));
    buffer = 0;
    pos    = 0;
}
