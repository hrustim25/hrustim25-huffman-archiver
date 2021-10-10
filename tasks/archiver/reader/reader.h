#include <fstream>
#include <string>

class Reader {
public:
    size_t Read1Bit();
    size_t Read9Bits();
    unsigned char ReadCharacter();
    bool HasCharacter();
    void OpenFile(std::string& file);
    void CloseFile();
private:
    std::ifstream in_stream;
    unsigned char buffer;
    int current_bit_position = 8;
};
