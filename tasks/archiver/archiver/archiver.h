#include <string>
#include <vector>

#include "../reader/reader.h"
#include "../writer/writer.h"

class Archiver {
public:
    void EncodeFiles(std::string& archive_name, std::vector<std::string>& files);
    void DecodeFile(std::string& archive_name);
private:
    Reader reader;
    Writer writer;
};
