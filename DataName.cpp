#include "DataName.h"

// Поиск структуры по типу и имени
DataName* findData(DataName* data, char type, const string& name) {
    while (data) {
        if (data->type == type && data->name == name) {
            return data;
        }
        data = data->next;
    }
    return nullptr;
}

// Создание новой структуры и добавление ее в список имен
DataName* addData(DataName*& data, char type, const string& name) {
    DataName* newData = new DataName{};
    newData->name = name;
    newData->type = type;
    if (type == 'A') newData->array = new SimpleArray(10);
    if (type == 'H') newData->hash = new HashTable(10);
    newData->next = data;
    data = newData;
    return newData;
}

// Освобождение дерева
void deleteNameTree(Tree* tree) {
    if (!tree) return;
    deleteNameTree(tree->left);
    deleteNameTree(tree->right);
    delete tree;
}

// Освобождение всех именованных структур при завершении программы
void deleteData(DataName*& data) {
    while (data) {
        DataName* current = data;
        data = data->next;
        while (current->stack.top) {
            StackNode* node = current->stack.top;
            current->stack.top = node->next;
            delete node;
        }
        while (current->queue.front) {
            QueueNode* node = current->queue.front;
            current->queue.front = node->next;
            delete node;
        }
        while (current->list) {
            ListNode* node = current->list;
            current->list = node->next;
            delete node;
        }
        while (current->head) {
            DoubleListNode* node = current->head;
            current->head = node->next;
            delete node;
        }
        deleteNameTree(current->tree);
        delete current->array;
        delete current->hash;
        delete current;
    }
}
