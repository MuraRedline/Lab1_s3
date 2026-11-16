#pragma once

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Узел бинарного дерева
struct Tree {
    int value;
    Tree* left;
    Tree* right;

    Tree(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Функции для работы с деревом
void addTree(Tree*& root, int value, ofstream& outFile);
void printTree(Tree* root, int level);
bool checkComplete(Tree* root, int index, int numberNodes, ofstream& outFile);
bool searchTree(Tree* root, int value, ofstream& outFile);

int countNumNodes(Tree* root);
