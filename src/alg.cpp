// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

bool isAlpha(char ch) {
    return std::isalpha(static_cast<unsigned char>(ch));
}

BST<std::string> makeTree(const char* filename) {
    BST<std::string> tree;
    std::ifstream input_file(filename);

    if (!input_file) {
        std::cout << "Error opening file!" << std::endl;
        return tree;
    }

    std::string line;
    while (std::getline(input_file, line)) {
        std::string word;
        for (char ch : line) {
            if (isAlpha(ch)) {
                word += std::tolower(static_cast<unsigned char>(ch));
            } else {
                if (!word.empty()) {
                    tree.insert(word);
                    word.clear();
                }
            }
        }

        if (!word.empty()) {
            tree.insert(word);
        }
    }

    input_file.close();
    return tree;
}
