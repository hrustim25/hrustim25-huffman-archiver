struct CanonicalCode {
    CanonicalCode(size_t representation_length, size_t character): character(character) {
        length = representation_length;
    }

    bool operator<(const CanonicalCode& code) const {
        return std::tie(length, character) < std::tie(code.length, code.character);
    }

    size_t representation = 0;
    size_t length = 0;
    size_t character = 0;
};
