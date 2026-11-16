#pragma once

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Узел стека
struct StackNode {
    string value;
    StackNode* next;
};

// Стек
struct Stack {
    StackNode* top; // Указатель на вершину стека
};

// Функции для работы со стеком
void push(Stack& stack, const string& value, ofstream& outFile);
void pop(Stack& stack, ofstream& outFile);
void printStack(const Stack& stack, ofstream& outFile);
