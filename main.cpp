#include "DataName.h"
#include <sstream>

// Убираем внешние пробелы и кавычки у значения
string readValue(const string& value) {
    size_t first = value.find_first_not_of(" \t\r");
    if (first == string::npos) return "";
    size_t last = value.find_last_not_of(" \t\r");
    string result = value.substr(first, last - first + 1);
    if (result.size() >= 2 && result[0] == '"' && result[result.size() - 1] == '"') {
        result = result.substr(1, result.size() - 2);
    }
    return result;
}

// Получение экземпляра. Создание разрешается только для команд добавления.
DataName* getData(DataName*& data, char type, const string& name, bool create) {
    DataName* current = findData(data, type, name);
    if (!current && create) current = addData(data, type, name);
    if (!current) cout << "Структура '" << name << "' не найдена." << endl;
    return current;
}

// Запись имени и команды в журнал текущего запуска
void logData(char type, const string& name, const string& command, ofstream& outFile) {
    outFile << "Структура: " << type << ", имя: " << name << endl;
    outFile << "Команда: " << command << endl;
    cout << "[" << name << "] ";
}

// Проверка целого числа для массива и дерева
bool checkNumber(const string& number) {
    try {
        size_t used = 0;
        stoi(number, &used);
        if (used == number.size()) return true;
    } catch (const exception&) {
    }
    cout << "Нужно ввести целое число в диапазоне int." << endl;
    return false;
}

// Чтение значения или пары аргументов после имени
bool readArguments(istringstream& input, string& value, string& first, int count) {
    if (count == 2 && !(input >> first)) {
        cout << "После имени нужны два аргумента." << endl;
        return false;
    }
    string text;
    getline(input >> ws, text);
    if ((count == 0 && !text.empty()) || (count != 0 && text.empty())) {
        cout << "Неверное количество аргументов команды." << endl;
        return false;
    }
    value = readValue(text);
    return true;
}

// Общая проверка только имени, без выбора типа и операции
bool readCommand(istringstream& input, string& operation, string& name) {
    if (input >> operation >> name) return true;
    cout << "Укажите команду и имя структуры." << endl;
    return false;
}

void Stackcom(DataName*& data, const string& command, ofstream& outFile) {
    istringstream input(command);
    string operation, name, value, first;
    if (!readCommand(input, operation, name)) return;

    int count;
    if (operation == "SPUSH") count = 1;
    else if (operation == "SPOP" || operation == "PRINT") count = 0;
    else {
        cout << "Неизвестная команда для выбранной структуры." << endl;
        return;
    }
    if (!readArguments(input, value, first, count)) return;
    DataName* current = getData(data, 'S', name, operation == "SPUSH");
    if (!current) return;
    logData('S', name, command, outFile);

    if (operation == "SPUSH") push(current->stack, value, outFile);
    else if (operation == "SPOP") pop(current->stack, outFile);
    else printStack(current->stack, outFile);
    outFile.flush();
}

void Queuecom(DataName*& data, const string& command, ofstream& outFile) {
    istringstream input(command);
    string operation, name, value, first;
    if (!readCommand(input, operation, name)) return;

    int count;
    if (operation == "QPUSH") count = 1;
    else if (operation == "QPOP" || operation == "PRINT") count = 0;
    else {
        cout << "Неизвестная команда для выбранной структуры." << endl;
        return;
    }
    if (!readArguments(input, value, first, count)) return;
    DataName* current = getData(data, 'Q', name, operation == "QPUSH");
    if (!current) return;
    logData('Q', name, command, outFile);

    if (operation == "QPUSH") enqueue(current->queue, value, outFile);
    else if (operation == "QPOP") dequeue(current->queue, outFile);
    else printQueue(current->queue, outFile);
    outFile.flush();
}

void Listcom(DataName*& data, const string& command, ofstream& outFile) {
    istringstream input(command);
    string operation, name, value, first;
    if (!readCommand(input, operation, name)) return;

    int count;
    if (operation == "LPUSH" || operation == "LAPPEND" || operation == "LREMOVE" || operation == "LGET" ||
        operation == "LDELBEFORE" || operation == "LDELAFTER") count = 1;
    else if (operation == "LBEFORE" || operation == "LAFTER") count = 2;
    else if (operation == "LDELHEAD" || operation == "LDELEND" || operation == "PRINT") count = 0;
    else {
        cout << "Неизвестная команда для выбранной структуры." << endl;
        return;
    }
    if (!readArguments(input, value, first, count)) return;
    DataName* current = getData(data, 'L', name, operation == "LPUSH" || operation == "LAPPEND");
    if (!current) return;
    logData('L', name, command, outFile);

    if (operation == "LPUSH") listInsertHead(current->list, value, outFile, "LPUSH");
    else if (operation == "LAPPEND") listInsertTail(current->list, value, outFile, "LAPPEND");
    else if (operation == "L") listInsertBefore(current->list, readValue(first), value, outFile);
    else if (operation == "LAFTER") listInsertAfter(current->list, readValue(first), value, outFile);
    else if (operation == "LDELBEFORE") listDeleteBefore(current->list, value, outFile);
    else if (operation == "LDELAFTER") listDeleteAfter(current->list, value, outFile);
    else if (operation == "LREMOVE") listDelete(current->list, value, outFile);
    else if (operation == "LGET") listGet(current->list, value, outFile);
    else if (operation == "LDELHEAD") listDeleteHead(current->list, outFile);
    else if (operation == "LDELEND") listDeleteEnd(current->list, outFile);
    else if (operation == "PRINT") listPrint(current->list, outFile, "PRINT");
    outFile.flush();
}

void DListcom(DataName*& data, const string& command, ofstream& outFile) {
    istringstream input(command);
    string operation, name, value, first;
    if (!readCommand(input, operation, name)) return;

    int count;
    if (operation == "DPUSH" || operation == "DAPPEND" || operation == "DREMOVE" || operation == "DGET" ||
        operation == "DDELBEFORE" || operation == "DDELAFTER") count = 1;
    else if (operation == "DBEFORE" || operation == "DAFTER") count = 2;
    else if (operation == "DDELHEAD" || operation == "DDELEND" || operation == "PRINT") count = 0;
    else {
        cout << "Неизвестная команда для выбранной структуры." << endl;
        return;
    }
    if (!readArguments(input, value, first, count)) return;
    DataName* current = getData(data, 'D', name, operation == "DPUSH" || operation == "DAPPEND");
    if (!current) return;
    logData('D', name, command, outFile);

    if (operation == "DPUSH") dlistInsertHead(current->head, current->tail, value, outFile, "DPUSH");
    else if (operation == "DAPPEND") dlistInsertTail(current->head, current->tail, value, outFile, "DAPPEND");
    else if (operation == "DBEFORE") dlistInsertBefore(current->head, readValue(first), value, outFile);
    else if (operation == "DAFTER") dlistInsertAfter(current->head, current->tail, readValue(first), value, outFile);
    else if (operation == "DDELBEFORE") dlistDeleteBefore(current->head, value, outFile);
    else if (operation == "DDELAFTER") dlistDeleteAfter(current->head, current->tail, value, outFile);
    else if (operation == "DREMOVE") dlistDelete(current->head, current->tail, value, outFile);
    else if (operation == "DGET") dlistGet(current->head, value, outFile);
    else if (operation == "DDELHEAD") dlistDeleteHead(current->head, current->tail, outFile);
    else if (operation == "DDELEND") dlistDeleteEnd(current->head, current->tail, outFile);
    else if (operation == "PRINT") dlistPrint(current->head, outFile, "PRINT");
    outFile.flush();
}

void Arraycom(DataName*& data, const string& command, ofstream& outFile) {
    istringstream input(command);
    string operation, name, value, first;
    if (!readCommand(input, operation, name)) return;

    int count;
    if (operation == "AADD") count = 1;
    else if (operation == "ADDINDEX" || operation == "AREPLACE") count = 2;
    else if (operation == "AREMOVE" || operation == "AGET") count = 1;
    else if (operation == "LENGTH" || operation == "PRINT") count = 0;
    else {
        cout << "Неизвестная команда для выбранной структуры." << endl;
        return;
    }
    if (!readArguments(input, value, first, count)) return;
    if ((operation == "ADDINDEX" || operation == "AREPLACE") && !checkNumber(first)) return;
    if ((operation == "AREMOVE" || operation == "AGET") && !checkNumber(value)) return;
    if (operation == "ADDINDEX" && !findData(data, 'A', name) && stoi(first) != 0) {
        cout << "Первый элемент можно добавить только по индексу 0." << endl;
        return;
    }
    DataName* current = getData(data, 'A', name, operation == "AADD" || operation == "ADDINDEX");
    if (!current) return;
    logData('A', name, command, outFile);

    if (operation == "AADD") add(*current->array, value);
    else if (operation == "ADDINDEX") addAtIndex(*current->array, first, value);
    else if (operation == "AREPLACE") replaceItem(*current->array, first, value);
    else if (operation == "AREMOVE") removeAtIndex(*current->array, value);
    else if (operation == "AGET") getItem(*current->array, value);
    else if (operation == "LENGTH") getLength(*current->array);
    else if (operation == "PRINT") printArray(*current->array);
    outFile.flush();
}

void Treecom(DataName*& data, const string& command, ofstream& outFile) {
    istringstream input(command);
    string operation, name, value, first;
    if (!readCommand(input, operation, name)) return;

    int count;
    if (operation == "TADD" || operation == "TSEARCH") count = 1;
    else if (operation == "TCOMPLETE" || operation == "PRINT") count = 0;
    else {
        cout << "Неизвестная команда для выбранной структуры." << endl;
        return;
    }
    if (!readArguments(input, value, first, count)) return;
    if (count == 1 && !checkNumber(value)) return;
    DataName* current = getData(data, 'T', name, operation == "TADD");
    if (!current) return;
    logData('T', name, command, outFile);

    if (operation == "TADD") addTree(current->tree, stoi(value), outFile);
    else if (operation == "TSEARCH") {
        if (!searchTree(current->tree, stoi(value), outFile)) {
            outFile << "SEARCH " << value << ": not found" << endl;
            cout << "Элемент '" << value << "' не найден в дереве." << endl;
        }
    }
    else if (operation == "TCOMPLETE") {
        if (checkComplete(current->tree, 0, countNumNodes(current->tree), outFile)) {
            outFile << "COMPLETE: yes" << endl;
            cout << "Дерево является полным." << endl;
        } else {
            cout << "Дерево не является полным." << endl;
        }
    }
    else if (operation == "PRINT") printTree(current->tree, 0);
    outFile.flush();
}

void HashTablecom(DataName*& data, const string& command, ofstream& outFile) {
    istringstream input(command);
    string operation, name, value, first;
    if (!readCommand(input, operation, name)) return;

    int count;
    if (operation == "HSET") count = 2;
    else if (operation == "HGET" || operation == "HDEL") count = 1;
    else if (operation == "PRINT") count = 0;
    else {
        cout << "Неизвестная команда для выбранной структуры." << endl;
        return;
    }
    if (!readArguments(input, value, first, count)) return;
    DataName* current = getData(data, 'H', name, operation == "HSET");
    if (!current) return;
    logData('H', name, command, outFile);

    if (operation == "HSET") current->hash->HSET(first, value, outFile);
    else if (operation == "HGET") current->hash->HGET(value, outFile);
    else if (operation == "HDEL") current->hash->HDEL(value, outFile);
    else if (operation == "PRINT") current->hash->PRINT(outFile);
    outFile.flush();
}

// Очистка файла журнала
void clearFile(const string& fileName) {
    ofstream file(fileName, ios::out);
    if (!file.is_open()) {
        cerr << "Не удалось очистить файл: " << fileName << endl;
    }
}

int main(int argc, char** argv) {
    if (argc != 3 || string(argv[1]) != "--file") {
        cerr << "Использование: ./program --file file.data" << endl;
        return 1;
    }

    string fileName = argv[2];
    ofstream outFile(fileName, ios::out); // Новый журнал для текущего запуска
    if (!outFile.is_open()) {
        cerr << "Не удалось открыть файл для записи: " << fileName << endl;
        return 1;
    }

    DataName* data = nullptr; // Список именованных структур
    cout << "Введите команду:  Для выхода введите EXIT." << endl;
    string command;
    while (true) {
        cout << "> ";
        if (!getline(cin, command)) break;
        if (command == "EXIT") {
            break;
        } else if (command == "CLEAR") {
            outFile.close();
            outFile.open(fileName, ios::out);
            cout << "Файл очищен. Структуры остаются в памяти." << endl;
        } else {
            istringstream input(command);
            string type;
            input >> type;
            if (type.empty()) continue;
            string operation;
            getline(input >> ws, operation);
            // Тип структуры определяется первой буквой первого слова.
            if (type[0] == 'S') Stackcom(data, operation, outFile);
            else if (type[0] == 'Q') Queuecom(data, operation, outFile);
            else if (type[0] == 'L') Listcom(data, operation, outFile);
            else if (type[0] == 'D') DListcom(data, operation, outFile);
            else if (type[0] == 'A') Arraycom(data, operation, outFile);
            else if (type[0] == 'T') Treecom(data, operation, outFile);
            else if (type[0] == 'H') HashTablecom(data, operation, outFile);
            else {
                cout << "Неизвестная структура данных." << endl;
            }
        }
    }

    deleteData(data); // Освобождаем все созданные структуры
    outFile.close();
    clearFile(fileName); // После остановки элементы в файле не сохраняются
    return 0;
}
