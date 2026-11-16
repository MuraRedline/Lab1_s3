#pragma once

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Узел односвязного списка
struct ListNode {
    string value;
    ListNode* next;
};

// Функции для работы с односвязным списком
void listInsertHead(ListNode*& head, const string& value, ofstream& outFile, const string& operation);
void listInsertTail(ListNode*& head, const string& value, ofstream& outFile, const string& operation);
void listInsertBefore(ListNode*& head, const string& target, const string& value, ofstream& outFile);
void listInsertAfter(ListNode* head, const string& target, const string& value, ofstream& outFile);
void listDeleteBefore(ListNode*& head, const string& target, ofstream& outFile);
void listDeleteAfter(ListNode* head, const string& target, ofstream& outFile);
void listDelete(ListNode*& head, const string& value, ofstream& outFile);
void listDeleteHead(ListNode*& head, ofstream& outFile);
void listDeleteEnd(ListNode*& head, ofstream& outFile);
void listGet(ListNode* head, const string& value, ofstream& outFile);
void listPrint(ListNode* head, ofstream& outFile, const string& operation);
