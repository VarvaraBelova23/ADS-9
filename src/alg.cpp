// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cctype>
#include "bst.h"

BST<std::string> makeTree(const char* filename) {
    BST<std::string> tree;
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return tree;
    }

    std::string word;
    while (file >> word) {
        std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) {
            return std::tolower(c);
        });

        std::string cleanedWord;
        for (char c : word) {
            if (std::isalpha(c)) {
                cleanedWord += c;
            }
        }

        if (!cleanedWord.empty()) {
            tree.insert(cleanedWord);
        }
    }

    file.close();
    return tree;
}
