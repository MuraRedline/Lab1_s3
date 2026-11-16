#pragma once

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct SimpleArray {
    string* data;    // Указатель на массив строк
    int size;        // Текущий размер массива
    int capacity;    // Вместимость массива

    SimpleArray(int cap);  // Конструктор
    ~SimpleArray();        // Деструктор
};

// Функции работы с массивом
void add(SimpleArray& arr, const string& value);
void addAtIndex(SimpleArray& arr, const string& index, const string& value);
void removeAtIndex(SimpleArray& arr, const string& index);
void getItem(const SimpleArray& arr, const string& index);
void replaceItem(SimpleArray& arr, const string& index, const string& value);
void printArray(const SimpleArray& arr);
void getLength(const SimpleArray& arr);
