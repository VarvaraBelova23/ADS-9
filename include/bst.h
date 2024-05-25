// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>
#include <memory>
#include <utility>

template <typename T>
class BST {
 public:
    struct Node {
        T value;
        int count;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        explicit Node(const T& val)
            : value(val), count(1), left(nullptr), right(nullptr) {}
    };

    BST() : root(nullptr) {}

    void insert(const T& value) {
        root = insertImpl(std::move(root), value);
    }

    int search(const T& value) const {
        const Node* node = searchImpl(root.get(), value);
        return node ? node->count : 0;
    }

    int depth() const {
        return depthImpl(root.get()) - 1;
    }

 private:
    std::unique_ptr<Node> root;

    std::unique_ptr<Node> insertImpl(std::unique_ptr<Node> node, const T& value) {
        if (!node) {
            return std::make_unique<Node>(value);
        }

        if (value == node->value) {
            node->count++;
        } else if (value < node->value) {
            node->left = insertImpl(std::move(node->left), value);
        } else {
            node->right = insertImpl(std::move(node->right), value);
        }

        return node;
    }

    const Node* searchImpl(const Node* node, const T& value) const {
        if (!node || node->value == value) {
            return node;
        }

        if (value < node->value) {
            return searchImpl(node->left.get(), value);
        } else {
            return searchImpl(node->right.get(), value);
        }
    }

    int depthImpl(const Node* node) const {
        if (!node) {
            return 0;
        }
        int leftDepth = depthImpl(node->left.get());
        int rightDepth = depthImpl(node->right.get());
        return std::max(leftDepth, rightDepth) + 1;
    }
};

#endif  // INCLUDE_BST_H_
