#include "dlist.h"

// Добавление элемента в голову двусвязного списка
// Создает новый узел и добавляет его в начало списка
void dlistInsertHead(DoubleListNode*& head, DoubleListNode*& tail, const string& value, ofstream& outFile, const string& operation) {
    DoubleListNode* newNode = new DoubleListNode{value, head, nullptr}; // Создаем новый узел
    if (head) head->prev = newNode; // Устанавливаем связь между новым узлом и текущей головой
    head = newNode; // Новый узел становится головой
    if (!tail) tail = newNode; // Если список был пуст, хвост также указывает на новый узел
    cout << "Элемент '" << value << "' добавлен в двусвязный список (в голову)." << endl;
}

// Добавление элемента в хвост двусвязного списка
// Создает новый узел и добавляет его в конец списка
void dlistInsertTail(DoubleListNode*& head, DoubleListNode*& tail, const string& value, ofstream& outFile, const string& operation) {
    DoubleListNode* newNode = new DoubleListNode{value, nullptr, tail}; // Создаем новый узел
    if (tail) tail->next = newNode; // Устанавливаем связь между текущим хвостом и новым узлом
    tail = newNode; // Новый узел становится хвостом
    if (!head) head = newNode; // Если список был пуст, голова также указывает на новый узел
    cout << "Элемент '" << value << "' добавлен в двусвязный список (в хвост)." << endl;
}
// Вставка после первым узлом с заданным значением
void dlistInsertAfter(DoubleListNode* head, DoubleListNode*& tail, const string& target, const string& value, ofstream& outFile){
    DoubleListNode* current = head;
    while (current && current->value != target) {
        current = current->next;
    }
    DoubleListNode* newNode = new DoubleListNode{value, current->next, current};
    if (current->next) {
        current -> next -> prev = newNode;
    } else {
        tail = newNode;
    } 
    current -> next = newNode;
    cout << "Элемент " << value << " добавлен после " << target << " ." << endl;
};
// Вставка перед первым узлом с заданным значением
void dlistInsertBefore(DoubleListNode*& head, const string& target, const string& value, ofstream& outFile) {
    DoubleListNode* current = head;
    while (current && current->value != target) {
        current = current->next;
    }
    DoubleListNode* newNode = new DoubleListNode{value, current, current->prev};
    if (current->prev) {
        current->prev->next = newNode;
    }   else {
        head = newNode;
    }
    current->prev = newNode;
    cout << "Элемент '" << value << "' добавлен перед '" << target << "'." << endl;
}
// Удаление соседа перед первым узлом с заданным значением
void dlistDeleteBefore(DoubleListNode*& head, const string& target, ofstream& outFile) {
    DoubleListNode* current = head;
    while (current && current->value != target) {
        current = current->next;
    }
    DoubleListNode* temp = current->prev;
    current->prev = temp->prev;
    if (temp->prev) {
        temp->prev->next = current;
    } else {
        head = current;
    }
    cout << "Элемент '" << temp->value << "' перед '" << target << "' удалён." << endl;
    delete temp;
}

// Удаление соседа после первым узлом с заданным значением
void dlistDeleteAfter(DoubleListNode* head, DoubleListNode*& tail, const string& target, ofstream& outFile) {
    DoubleListNode* current = head;
    while (current && current->value != target) {
        current = current->next;
    }
    DoubleListNode* temp = current->next;
    current->next = temp->next;
    if (temp->next) {
        temp->next->prev = current;
    } else {
        tail = current;
    }
    cout << "Элемент '" << temp->value << "' после '" << target << "' удалён." << endl;
    delete temp;
}

// Удаление элемента из начала списка
// Удаляет узел из начала списка и освобождает память
void dlistDeleteHead(DoubleListNode*& head, DoubleListNode*& tail, ofstream& outFile) {
    if (!head) { // Проверяем, пуст ли список
        cout << "Список пуст! Нечего удалять." << endl;
        return;
    }

    DoubleListNode* temp = head; // Сохраняем текущую голову
    head = head->next; // Перемещаем голову на следующий узел
    if (head) head->prev = nullptr; // Удаляем связь с предыдущим узлом
    else tail = nullptr; // Если список стал пустым, сбрасываем хвост

    cout << "Элемент '" << temp->value << "' удалён из начала двусвязного списка." << endl;
    delete temp; // Освобождаем память
}

// Удаление элемента из конца списка
// Удаляет узел из конца списка и освобождает память
void dlistDeleteEnd(DoubleListNode*& head, DoubleListNode*& tail, ofstream& outFile) {
    if (!tail) { // Проверяем, пуст ли список
        cout << "Список пуст! Нечего удалять." << endl;
        return;
    }
    DoubleListNode* temp = tail; // Сохраняем текущий хвост
    tail = tail->prev; // Перемещаем хвост на предыдущий узел
    if (tail) tail->next = nullptr; // Удаляем связь с текущим узлом
    else head = nullptr; // Если список стал пустым, сбрасываем голову
    cout << "Элемент '" << temp->value << "' удалён из конца двусвязного списка." << endl;
    delete temp; // Освобождаем память
}

// Удаление элемента по значению
// Находит узел с указанным значением и удаляет его
void dlistDelete(DoubleListNode*& head, DoubleListNode*& tail, const string& value, ofstream& outFile) {
    DoubleListNode* current = head;
    while (current && current->value != value) { // Ищем узел с заданным значением
        current = current->next;
    }

    if (!current) { // Если узел не найден
        cout << "Элемент '" << value << "' не найден." << endl;
        return;
    }

    if (current->prev) current->prev->next = current->next; // Устанавливаем связь между предыдущим и следующим узлом
    else head = current->next; // Если удаляем голову, сдвигаем её

    if (current->next) current->next->prev = current->prev; // Устанавливаем связь между следующим и предыдущим узлом
    else tail = current->prev; // Если удаляем хвост, сдвигаем его

    delete current; // Удаляем узел
    cout << "Элемент '" << value << "' удалён из двусвязного списка." << endl;
}

// Поиск элемента
// Ищет элемент в списке и выводит результат
void dlistGet(DoubleListNode* head, const string& value, ofstream& outFile) {
    while (head) { // Перебираем элементы списка
        if (head->value == value) { // Если найдено совпадение
            cout << "Число '" << value << "' найдено в двусвязном списке." << endl;
            return;
        }
        head = head->next; // Переходим к следующему узлу
    }
    cout << "Число '" << value << "' не найдено в двусвязном списке." << endl;
}

// Печать содержимого двусвязного списка
// Выводит все элементы списка
void dlistPrint(DoubleListNode* head, ofstream& outFile, const string& operation) {
    if (!head) { // Проверяем, пуст ли список
        cout << "Список пуст!" << endl;
        outFile << operation << ": empty" << endl;
        return;
    }

    cout << "Содержимое двусвязного списка: ";
    while (head) { // Перебираем элементы списка
        cout << head->value << " ";
        outFile << head->value << " ";
        head = head->next; // Переходим к следующему узлу
    }
    cout << endl;
    outFile << endl;
}
