#include <algorithm>
#include <queue>
#include <tuple>

#include "archiver.h"
#include "canonical_haffman_code.cpp"
#include "trie_vertex.h"
#include "priority_queue.cpp"

using PQueue = PriorityQueue<std::shared_ptr<TrieVertex>, TrieVertex::Compare>;

namespace {
    const size_t FILENAME_END = 256;
    const size_t ONE_MORE_FILE = 257;
    const size_t ARCHIVE_END = 258;
    const size_t ALPHABET_CAPACITY = 259;

    size_t byte_count[ALPHABET_CAPACITY] = {0};
    size_t matching_code[ALPHABET_CAPACITY] = {0};
    size_t matching_code_length[ALPHABET_CAPACITY] = {0};
    size_t code_size_count[ALPHABET_CAPACITY] = {0};
    std::vector<CanonicalCode> haffman_codes;
    size_t symbols_count = 0;
    PQueue queue;
    std::shared_ptr<TrieVertex> trie_root = nullptr;
}

void TrieDFS(std::shared_ptr<TrieVertex> vertex, size_t current_length) {
    if (vertex->IsTerminal()) {
        haffman_codes.push_back(CanonicalCode(current_length, vertex->GetCharacter()));
        return;
    }
    TrieDFS(vertex->GetLeftChild(), current_length + 1);
    TrieDFS(vertex->GetRightChild(), current_length + 1);
}

void MakeCanonicalForm() {
    sort(haffman_codes.begin(), haffman_codes.end());
    for (size_t i = 1; i < haffman_codes.size(); ++i) {
        haffman_codes[i].representation = haffman_codes[i - 1].representation;
        ++haffman_codes[i].representation;
        haffman_codes[i].representation <<= haffman_codes[i].length - haffman_codes[i - 1].length;
    }
    for (size_t i = 1; i < haffman_codes.size(); ++i) {
        size_t old_representation = haffman_codes[i].representation;
        haffman_codes[i].representation = 0;
        for (size_t j = 0; j < haffman_codes[i].length; ++j) {
            haffman_codes[i].representation += static_cast<size_t>((old_representation &
                                               (1 << (haffman_codes[i].length - 1 - j))) > 0) << j;
        }
    }
}

void BuildTrie(std::string& current_file) {
    for (size_t i = 0; i < ALPHABET_CAPACITY; ++i) {
        if (byte_count[i] > 0) {
            ++symbols_count;
            std::shared_ptr<TrieVertex> vertex = std::make_shared<TrieVertex>(byte_count[i], true, i);
            queue.push(vertex);
        }
    }

    while (queue.size() >= 2) {
        std::shared_ptr<TrieVertex> left_child = queue.top();
        queue.pop();
        std::shared_ptr<TrieVertex> right_child = queue.top();
        queue.pop();

        std::shared_ptr<TrieVertex> parent = CreateParent(left_child, right_child);
        queue.push(parent);
    }
    trie_root = queue.top();
    queue.pop();

    haffman_codes.reserve(symbols_count);
    TrieDFS(trie_root, 0);

    MakeCanonicalForm();

    for (const CanonicalCode& code : haffman_codes) {
        matching_code[code.character] = code.representation;
        matching_code_length[code.character] = code.length;
        ++code_size_count[code.length - 1];
    }
}

void Archiver::EncodeFiles(std::string& archive_name, std::vector<std::string>& files) {
    writer.OpenFile(archive_name);
    for (size_t file_index = 0; file_index < files.size(); ++file_index) {
        std::string& current_file = files[file_index];
        for (size_t i = 0; i < ALPHABET_CAPACITY; ++i) {
            byte_count[i] = 0;
            matching_code[i] = 0;
            matching_code_length[i] = 0;
            code_size_count[i] = 0;
        }
        symbols_count = 0;
        haffman_codes.clear();
        trie_root = nullptr;

        reader.OpenFile(current_file);
        while (reader.HasCharacter()) {
            unsigned char character = reader.ReadCharacter();
            if (!reader.HasCharacter()) {
                break;
            }
            ++byte_count[character];
        }
        for (unsigned char character : current_file) {
            ++byte_count[character];
        }
        byte_count[FILENAME_END] = 1;
        byte_count[ONE_MORE_FILE] = 1;
        byte_count[ARCHIVE_END] = 1;
        BuildTrie(current_file);
        reader.CloseFile();

        reader.OpenFile(current_file);
        writer.Write9Bits(symbols_count);  // 1
        for (CanonicalCode& code : haffman_codes) {
            writer.Write9Bits(code.character);  // 2.1
        }
        size_t max_symbol_code_size = 0;
        for (size_t i = 0; i < ALPHABET_CAPACITY; ++i) {
            if (code_size_count[i] > 0) {
                max_symbol_code_size = i + 1;
            }
        }
        for (size_t i = 0; i < max_symbol_code_size; ++i) {
            writer.Write9Bits(code_size_count[i]);  // 2.2
        }

        for (unsigned char character : current_file) {
            writer.WriteHaffmanCode(matching_code[character], matching_code_length[character]);  // 3
        }
        writer.WriteHaffmanCode(matching_code[FILENAME_END], matching_code_length[FILENAME_END]);  // 4

        while (reader.HasCharacter()) {
            unsigned char character = reader.ReadCharacter();
            if (!reader.HasCharacter()) {
                break;
            }
            writer.WriteHaffmanCode(matching_code[character], matching_code_length[character]);  // 5
        }

        if (file_index + 1 < files.size()) {
            writer.WriteHaffmanCode(matching_code[ONE_MORE_FILE], matching_code_length[ONE_MORE_FILE]);  // 6
        } else {
            writer.WriteHaffmanCode(matching_code[ARCHIVE_END], matching_code_length[ARCHIVE_END]);  // 7
        }

        reader.CloseFile();
    }
    writer.PushBufferAndCloseFile();
}

void AddBranchToTrie(std::shared_ptr<TrieVertex> vertex, CanonicalCode& code, size_t index) {
    if (index == code.length) {
        vertex->SetCharacter(code.character);
        vertex->SetType(true);
        return;
    }
    if ((code.representation & (static_cast<size_t>(1) << index)) == 0) {
        if (vertex->GetLeftChild() == nullptr) {
            vertex->SetLeftChild(std::make_shared<TrieVertex>(false));
        }
        AddBranchToTrie(vertex->GetLeftChild(), code, index + 1);
    } else {
        if (vertex->GetRightChild() == nullptr) {
            vertex->SetRightChild(std::make_shared<TrieVertex>(false));
        }
        AddBranchToTrie(vertex->GetRightChild(), code, index + 1);
    }
}

void Archiver::DecodeFile(std::string& archive_name) {
    reader.OpenFile(archive_name);

    bool is_archive_end = false;
    while (!is_archive_end) {
        haffman_codes.clear();

        size_t symbols_count = reader.Read9Bits();
        size_t temp_character_array[symbols_count];
        for (size_t i = 0; i < symbols_count; ++i) {
            temp_character_array[i] = reader.Read9Bits();
        }
        size_t count_of_codes = 0;
        size_t current_code_size = 1;
        while (count_of_codes < symbols_count) {
            size_t current_code_size_count = reader.Read9Bits();
            code_size_count[current_code_size - 1] = current_code_size_count;
            count_of_codes += current_code_size_count;
            ++current_code_size;
        }
        haffman_codes.reserve(symbols_count);
        current_code_size = 0;
        for (size_t i = 0; i < symbols_count; ++i) {
            while (code_size_count[current_code_size] == 0) {
                ++current_code_size;
            }
            haffman_codes.push_back(CanonicalCode(current_code_size + 1, temp_character_array[i]));
            --code_size_count[current_code_size];
        }
        MakeCanonicalForm();
        trie_root = std::make_shared<TrieVertex>(false);
        for (size_t i = 0; i < haffman_codes.size(); ++i) {
            AddBranchToTrie(trie_root, haffman_codes[i], 0);
        }

        std::string file_name;
        bool is_file_name_end = false;
        std::shared_ptr<TrieVertex> current_vertex = trie_root;
        while (!is_file_name_end) {
            size_t bit = reader.Read1Bit();
            if (bit == 0) {
                current_vertex = current_vertex->GetLeftChild();
            } else {
                current_vertex = current_vertex->GetRightChild();
            }

            if (current_vertex->IsTerminal()) {
                size_t character = current_vertex->GetCharacter();
                if (character == FILENAME_END) {
                    is_file_name_end = true;
                    break;
                } else {
                    file_name += static_cast<unsigned char>(current_vertex->GetCharacter());
                    current_vertex = trie_root;
                }
            }
        }
        writer.OpenFile(file_name);

        bool is_data_end = false;
        current_vertex = trie_root;
        while (!is_data_end) {
            size_t bit = reader.Read1Bit();
            if (bit == 0) {
                current_vertex = current_vertex->GetLeftChild();
            } else {
                current_vertex = current_vertex->GetRightChild();
            }

            if (current_vertex->IsTerminal()) {
                if (current_vertex->GetCharacter() == ARCHIVE_END) {
                    is_data_end = true;
                    is_archive_end = true;
                    break;
                } else if (current_vertex->GetCharacter() == ONE_MORE_FILE) {
                    is_data_end = true;
                    break;
                }
                writer.Write8Bits(current_vertex->GetCharacter());
                current_vertex = trie_root;
            }
        }

        writer.PushBufferAndCloseFile();
    }

    reader.CloseFile();
}
