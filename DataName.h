#pragma once

#include "stack.h"
#include "queue.h"
#include "dlist.h"
#include "list.h"
#include "tree.h"
#include "array.h"
#include "hashtable.h"

// Узел списка именованных структур
struct DataName {
    string name;
    char type;
    Stack stack;
    Queue queue;
    ListNode* list;
    DoubleListNode* head;
    DoubleListNode* tail;
    Tree* tree;
    SimpleArray* array;
    HashTable* hash;
    DataName* next;
};

// Функции работы с именами структур (DataName.cpp)
DataName* findData(DataName* data, char type, const string& name);
DataName* addData(DataName*& data, char type, const string& name);
void deleteData(DataName*& data);
