#include <cstddef>

class TrieVertex {
public:
    TrieVertex(bool type);
    TrieVertex(size_t character_count, bool type, size_t character);
    ~TrieVertex();

    void SetLeftChild(TrieVertex* vertex);
    TrieVertex* GetLeftChild() const;
    void SetRightChild(TrieVertex* vertex);
    TrieVertex* GetRightChild() const;

    void SetCharacter(size_t new_character);
    size_t GetCharacter() const;
    bool IsTerminal() const;
    void SetType(bool type);
    size_t GetCharacterCount() const;
    struct Compare {
        bool operator() (const TrieVertex* const& vertex1, const TrieVertex* const& vertex2) const {
            return vertex1->GetCharacterCount() < vertex2->GetCharacterCount();
        }
    };
private:
    TrieVertex* left_child = nullptr;
    TrieVertex* right_child = nullptr;
    size_t character_count = 0;
    bool is_terminal = true;
    size_t character = 0;
};

TrieVertex* CreateParent(TrieVertex* left_child, TrieVertex* right_child);
