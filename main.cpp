#include <iostream>
#include <string>

#include "archiver/archiver.h"

void PrintCWrongFormat() {
    std::cout << "Command 'archiver -c' has this format:\n";
    std::cout << "archiver -c archive_name file1 [file2 ...]\n\n";
    std::cout << "Run 'archiver -h' for more details.\n";
}

void PrintDWrongFormat() {
    std::cout << "Command 'archiver -d' has this format:\n";
    std::cout << "archiver -d archive_name\n\n";
    std::cout << "Run 'archiver -h' for more details.\n";
}

void PrintUnknownCommand() {
    std::cout << "Unknown command\n";
    std::cout << "Run 'archiver -h' for more information.\n";
}

void PrintHelp() {
    std::cout << "Archiver v1.0.0\n\n";
    std::cout << "File Archiver based on Haffman algorithm.\n\n";
    std::cout << "Options:\n";
    std::cout << "  archiver -c archive_name file1 [file2 ...]   = Compress files 'file1', 'file2', ...\n";
    std::cout << "                                                 into 'archive_name' archive.\n";
    std::cout << "  archiver -d archive_name                     = Decompress archive 'archive_name'.\n";
    std::cout << "  archiver -h                                  = Get help.\n";
}

void work(int argc, char* argv[]) {
    Archiver a;
    
    if (argc == 1) {
        std::cout << "Please enter the command.\n";
        std::cout << "Run 'archiver -h' for more information.\n";
    } else if (argc == 2) {
        if (std::string(argv[1]) == "-h") {
            PrintHelp();
        } else if (std::string(argv[1]) == "-c") {
            PrintCWrongFormat();
        } else if (std::string(argv[1]) == "-d") {
            PrintDWrongFormat();
        } else {
            PrintUnknownCommand();
        }
    } else {
        if (std::string(argv[1]) == "-h") {
            std::cout << "Command 'archiver -h' has this format:\n";
            std::cout << "archiver -h\n";
        } else if (std::string(argv[1]) == "-c") {
            if (argc == 3) {
                PrintCWrongFormat();
            } else {
                std::string archive_name = argv[2];
                std::vector<std::string> files;
                for (int i = 3; i < argc; ++i) {
                    files.push_back(argv[i]);
                }
                a.EncodeFiles(archive_name, files);
            }
        } else if (std::string(argv[1]) == "-d") {
            if (argc > 3) {
                PrintDWrongFormat();
            } else {
                std::string archive_name = argv[2];
                a.DecodeFile(archive_name);
            }
        } else {
            PrintUnknownCommand();
        }
    }
}

int main(int argc, char* argv[]) {
    try {
        work(argc, argv);
    } catch(const std::string& error_message) {
        std::cout << error_message << std::endl;
    }
    return 0;
}
