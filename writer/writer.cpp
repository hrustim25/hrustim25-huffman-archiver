#include "writer.h"

void Writer::Write1Bit(size_t value) {
    if (current_bit_position == 8) {
        current_bit_position = 0;
        out_stream << buffer;
        buffer = 0;
    }
    buffer = buffer + static_cast<unsigned char>(value << current_bit_position);
    ++current_bit_position;
}

void Writer::WriteHaffmanCode(size_t code, size_t code_length) {
    for (size_t i = 0; i < code_length; ++i) {
        Write1Bit(static_cast<size_t>((code & (static_cast<size_t>(1) << i)) > 0));
    }
}

void Writer::Write8Bits(size_t value) {
    for (int i = 0; i < 8; ++i) {
        Writer::Write1Bit(static_cast<size_t>((value & (1 << i)) > 0));
    }
}

void Writer::Write9Bits(size_t value) {
    for (int i = 0; i < 9; ++i) {
        Writer::Write1Bit(static_cast<size_t>((value & (1 << i)) > 0));
    }
}

void Writer::OpenFile(const std::string& file) {
    out_stream.open(file);
}

void Writer::PushBufferAndCloseFile() {
    if (current_bit_position > 0) {
        current_bit_position = 0; 
        out_stream << buffer;
        buffer = 0;
    }
    out_stream.close();
}
