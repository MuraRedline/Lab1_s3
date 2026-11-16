#pragma once

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Структура для хранения пары ключ-значение
struct KeyValue {
    string key;
    string value;
};

struct Node {
    string key;
    string value;
    Node* next;

    Node(const string& k, const string& v) : key(k), value(v), next(nullptr) {}
};
// Класс хеш-таблицы
class HashTable {
private:
    int size;                  // Размер таблицы
    int* buckets;              // Массив для хранения индексов
    KeyValue* elements;        // Массив для хранения элементов
    int elementCount;          // Текущее количество элементов

    int hashFunction(const string& key);  // Хеш-функция
    int findSlot(const string& key, bool isInsert); // Поиск слота для ключа

public:
    HashTable(int s);          // Конструктор
    ~HashTable();              // Деструктор

    void HSET(const string& key, const string& value, ofstream& outFile); // Добавление элемента
    void HDEL(const string& key, ofstream& outFile);                     // Удаление элемента
    string HGET(const string& key, ofstream& outFile);                   // Получение значения по ключу
    void PRINT(ofstream& outFile);                                       // Печать таблицы
};                                       // Печать таблицы
