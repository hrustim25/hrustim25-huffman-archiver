#include <fstream>
#include <string>

class Writer {
public:
    void Write1Bit(size_t value);
    void Write8Bits(size_t value);
    void Write9Bits(size_t value);
    void WriteHaffmanCode(size_t code, size_t code_length);
    void OpenFile(std::string& file);
    void PushBufferAndCloseFile();
private:
    std::ofstream out_stream;
    unsigned char buffer;
    int current_bit_position = 0;
};
