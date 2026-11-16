#pragma once

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Узел очереди
struct QueueNode {
    string value;
    QueueNode* next;
};

// Очередь
struct Queue {
    QueueNode* front; // Указатель на первый элемент
    QueueNode* rear;  // Указатель на последний элемент
};

// Операции для очереди
void enqueue(Queue& queue, const string& value, ofstream& outFile);
void dequeue(Queue& queue, ofstream& outFile);
void printQueue(const Queue& queue, ofstream& outFile);
