// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>

template <typename T>
struct Node {
    T data;
    Node* left;
    Node* right;
    int count;

    Node(const T& value) : data(value), left(nullptr), right(nullptr), count(1) {}
};

template <typename T>
class BST {
private:
    Node<T>* root;

    Node<T>* insert(Node<T>* node, const T& value) {
        if (!node) {
            return new Node<T>(value);
        }

        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        } else {
            node->count++;
        }

        return node;
    }

    void inorder(Node<T>* node, std::ostream& os) const {
        if (node) {
            inorder(node->left, os);
            os << node->data << " (" << node->count << ")" << std::endl;
            inorder(node->right, os);
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(const T& value) {
        root = insert(root, value);
    }

    void inorder(std::ostream& os = std::cout) const {
        inorder(root, os);
    }
};

#endif  // INCLUDE_BST_H_
