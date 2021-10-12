#include "reader.h"

bool Reader::HasCharacter() const {
    return !in_stream.eof();
}

size_t Reader::Read1Bit() {
    size_t result = 0;
    if (current_bit_position == 8) {
        current_bit_position = 0;
        in_stream.read(reinterpret_cast<char*>(&buffer), 1);
    }
    result = static_cast<size_t>((buffer & (1 << current_bit_position)) > 0);
    ++current_bit_position;
    return result;
}

size_t Reader::Read9Bits() {
    size_t result = 0;
    for (int i = 0; i < 9; ++i) {
        result += Read1Bit() << i;
    }
    return result;
}

unsigned char Reader::ReadCharacter() {
    unsigned char result = 0;
    for (int i = 0; i < 8; ++i) {
        unsigned char tmp = Read1Bit();
        result += static_cast<unsigned char>(tmp > 0) << i;
    }
    return result;
}

void Reader::OpenFile(const std::string& file) {
    in_stream.open(file);
    if (in_stream.fail()) {
        std::string error_message = "File not found: " + file;
        throw error_message;
    }
}

void Reader::CloseFile() {
    in_stream.close();
}
