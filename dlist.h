#pragma once

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Узел двусвязного списка
struct DoubleListNode {
    string value;
    DoubleListNode* next;
    DoubleListNode* prev;
};

// Функции для работы с двусвязным списком
void dlistInsertHead(DoubleListNode*& head, DoubleListNode*& tail, const string& value, ofstream& outFile, const string& operation);
void dlistInsertTail(DoubleListNode*& head, DoubleListNode*& tail, const string& value, ofstream& outFile, const string& operation);
void dlistInsertBefore(DoubleListNode*& head, const string& target, const string& value, ofstream& outFile);
void dlistInsertAfter(DoubleListNode* head, DoubleListNode*& tail, const string& target, const string& value, ofstream& outFile);
void dlistDeleteBefore(DoubleListNode*& head, const string& target, ofstream& outFile);
void dlistDeleteAfter(DoubleListNode* head, DoubleListNode*& tail, const string& target, ofstream& outFile);
void dlistDeleteHead(DoubleListNode*& head, DoubleListNode*& tail, ofstream& outFile);
void dlistDeleteEnd(DoubleListNode*& head, DoubleListNode*& tail, ofstream& outFile);
void dlistDelete(DoubleListNode*& head, DoubleListNode*& tail, const string& value, ofstream& outFile);
void dlistGet(DoubleListNode* head, const string& value, ofstream& outFile);
void dlistPrint(DoubleListNode* head, ofstream& outFile, const string& operation);
