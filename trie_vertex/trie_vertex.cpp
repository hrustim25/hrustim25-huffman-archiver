#include "trie_vertex.h"

TrieVertex::TrieVertex(bool type): is_terminal(type) {}

TrieVertex::TrieVertex(size_t character_count, bool type, size_t character): character_count(character_count),
                                                                             character(character), is_terminal(type) {}

void TrieVertex::SetLeftChild(std::shared_ptr<TrieVertex> vertex) {
    left_child = vertex;
}

std::shared_ptr<TrieVertex> TrieVertex::GetLeftChild() const {
    return left_child;
}

void TrieVertex::SetRightChild(std::shared_ptr<TrieVertex> vertex) {
    right_child = vertex;
}

std::shared_ptr<TrieVertex> TrieVertex::GetRightChild() const {
    return right_child;
}

std::shared_ptr<TrieVertex> CreateParent(std::shared_ptr<TrieVertex>& left_child,
                                         std::shared_ptr<TrieVertex>& right_child) {
    std::shared_ptr<TrieVertex> parent = std::make_shared<TrieVertex>(left_child->GetCharacterCount() +
                                                          right_child->GetCharacterCount(), false, 0);
    parent->SetLeftChild(left_child);
    parent->SetRightChild(right_child);
    return parent;
}

void TrieVertex::SetCharacter(size_t new_character) {
    character = new_character;
}

size_t TrieVertex::GetCharacter() const {
    return character;
}

void TrieVertex::SetType(bool type) {
    is_terminal = type;
}

bool TrieVertex::IsTerminal() const {
    return is_terminal;
}

size_t TrieVertex::GetCharacterCount() const {
    return character_count;
}
