// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>

template<typename T>
struct Node {
    T key;
    int count;
    Node *left, *right;

    explicit Node(T value) : key(value), count(1), left(nullptr), right(nullptr) {}
};

template<typename T>
class BST {
private:
    Node<T> *root;

    int calculateHeight(Node<T> *node) {
        if (node == nullptr)
            return 0;
        int rightHeight = calculateHeight(node->right);
        int leftHeight = calculateHeight(node->left);
        return std::max(rightHeight, leftHeight) + 1;
    }

    Node<T> *insertNode(Node<T> *node, T value) {
        if (node == nullptr) {
            node = new Node<T>(value);
        } else if (node->key > value) {
            node->left = insertNode(node->left, value);
        } else if (node->key < value) {
            node->right = insertNode(node->right, value);
        } else {
            node->count++;
        }
        return node;
    }

    int findValue(Node<T> *node, T value) {
        if (node->key == value)
            return node->count;
        else if (node->key > value)
            return findValue(node->left, value);
        else if (node->key < value)
            return findValue(node->right, value);
        else
            return 0;
    }

    void deleteTreeNodes(Node<T> *node) {
        if (node == nullptr)
            return;
        deleteTreeNodes(node->right);
        deleteTreeNodes(node->left);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    void insert(T value) {
        root = insertNode(root, value);
    }

    int getHeight() {
        return calculateHeight(root) - 1;
    }

    int searchValue(T value) {
        return findValue(root, value);
    }

    ~BST() {
        deleteTreeNodes(root);
    }
};

#endif  // INCLUDE_BST_H_

alg.cpp:
cpp
#include <fstream>
#include <cctype>
#include "bst.h"

BST<std::string> makeTree(const char* filename) {
    std::ifstream file(filename);
    BST<std::string> tree;
    std::string word;
    while (!file.eof()) {
        char ch = file.get();
        if (ch != ' ' && isalpha(ch)) {
            ch = tolower(ch);
            word += ch;
        } else {
            tree.insert(word);
            word.clear();
        }
    }
    return tree;
}
