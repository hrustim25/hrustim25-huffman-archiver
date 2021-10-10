#include <stdexcept>
#include <string>
#include <vector>

template <typename T,
          class Compare = std::less<std::vector<T>>>
class PriorityQueue {
public:
    PriorityQueue() {
        tree.resize(1);
    }

    T top() const {
        if (tree.size() == 1) {
            std::string error_message = "Attempted to access empty container.";
            throw error_message;
        }
        return tree[1];
    }

    void pop() {
        if (tree.size() == 1) {
            std::string error_message = "Attempted to pop from empty container.";
            throw error_message;
        }
        tree[1] = tree.back();
        tree.pop_back();
        PullDown(1);
    }

    void push(const T& value) {
        tree.push_back(value);
        PullUp(tree.size() - 1);
    }

    size_t size() const {
        return tree.size() - 1;
    }
private:
    void PullUp(size_t index) {
        if (index == 1) {
            return;
        }
        if (comparator(tree[index], tree[index / 2])) {
            std::swap(tree[index / 2], tree[index]);
            PullUp(index / 2);
        }
    }

    void PullDown(size_t index) {
        if (index * 2 >= tree.size()) {
            return;
        }
        if (index * 2 + 1 >= tree.size()) {
            if (comparator(tree[index], tree[index * 2])) {
                std::swap(tree[index], tree[index * 2]);
                PullDown(index * 2);
            }
        } else {
            if (comparator(tree[index * 2], tree[index]) || comparator(tree[index * 2 + 1], tree[index])) {
                if (comparator(tree[index * 2], tree[index * 2 + 1])) {
                    std::swap(tree[index], tree[index * 2]);
                    PullDown(index * 2);
                } else {
                    std::swap(tree[index], tree[index * 2 + 1]);
                    PullDown(index * 2 + 1);
                }
            }
        }
    }

    std::vector<T> tree;
    Compare comparator;
};
