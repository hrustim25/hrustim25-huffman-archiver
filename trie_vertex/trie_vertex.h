#include <cstddef>
#include <memory>

class TrieVertex {
public:
    TrieVertex(bool type);
    TrieVertex(size_t character_count, bool type, size_t character);

    void SetLeftChild(std::shared_ptr<TrieVertex> vertex);
    std::shared_ptr<TrieVertex> GetLeftChild() const;
    void SetRightChild(std::shared_ptr<TrieVertex> vertex);
    std::shared_ptr<TrieVertex> GetRightChild() const;

    void SetCharacter(size_t new_character);
    size_t GetCharacter() const;
    bool IsTerminal() const;
    void SetType(bool type);
    size_t GetCharacterCount() const;
private:
    std::shared_ptr<TrieVertex> left_child = nullptr;
    std::shared_ptr<TrieVertex> right_child = nullptr;
    size_t character_count = 0;
    bool is_terminal = true;
    size_t character = 0;
};

std::shared_ptr<TrieVertex> CreateParent(std::shared_ptr<TrieVertex>& left_child,
                                         std::shared_ptr<TrieVertex>& right_child);
