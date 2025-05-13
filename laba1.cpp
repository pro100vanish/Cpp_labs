#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

//Инициализация списка с фиктивным элементом
Node* initList() {
    Node* sentinel = new Node;
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    return sentinel;
}

//Добавление в конец
void push_back(Node* sentinel, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = sentinel;
    newNode->prev = sentinel->prev;
    sentinel->prev->next = newNode;
    sentinel->prev = newNode;
}

//Печать списка
void printList(Node* sentinel) {
    Node* current = sentinel->next;
    while (current != sentinel) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

//Проверка наличия цифры
bool containsDigit(int number, int digit) {
    while (number > 0) {
        if (number % 10 == digit) return true;
        number /= 10;
    }
    return false;
}

//Проверка на дубликаты
bool hasDuplicates(Node* sentinel) {
    for (Node* i = sentinel->next; i != sentinel; i = i->next) {
        for (Node* j = i->next; j != sentinel; j = j->next) {
            if (i->data == j->data) return true;
        }
    }
    return false;
}

// 📊 Сортировка по невозрастанию последней цифры (пузырьком)
void sortByLastDigitDesc(Node* sentinel) {
    bool swapped;
    do {
        swapped = false;
        for (Node* i = sentinel->next; i->next != sentinel; i = i->next) {
            if ((i->data % 10) < (i->next->data % 10)) {
                int tmp = i->data;
                i->data = i->next->data;
                i->next->data = tmp;
                swapped = true;
            }
        }
    } while (swapped);
}

//Удаление узла
void deleteNode(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
}

// 🚮 Удалить числа, содержащие 3
void removeWith3(Node* sentinel) {
    Node* current = sentinel->next;
    while (current != sentinel) {
        Node* next = current->next;
        if (containsDigit(current->data, 3)) {
            deleteNode(current);
        }
        current = next;
    }
}

//Дублировать числа с 7 без 3
void duplicateWith7(Node* sentinel) {
    Node* current = sentinel->next;
    while (current != sentinel) {
        Node* next = current->next;
        if (containsDigit(current->data, 7) && !containsDigit(current->data, 3)) {
            Node* copy = new Node;
            copy->data = current->data;
            copy->next = next;
            copy->prev = current;
            current->next = copy;
            next->prev = copy;
            current = copy; // пропускаем дубликат
        }
        current = current->next;
    }
}

// 🧹 Очистка списка
void clearList(Node* sentinel) {
    Node* current = sentinel->next;
    while (current != sentinel) {
        Node* toDelete = current;
        current = current->next;
        delete toDelete;
    }
    delete sentinel;
}

int main() {
    Node* list = initList();
    int num;

    cout << "Введите натуральные числа (0 — завершение ввода):\n";
    while (cin >> num && num != 0) {
        if (num > 0) push_back(list, num);
    }

    if (hasDuplicates(list)) {
        cout << "Есть дубликаты. Сортировка по невозрастанию последней цифры:\n";
        sortByLastDigitDesc(list);
    } else {
        cout << "Дубликаты не найдены. Удаление чисел с 3 и дублирование с 7:\n";
        removeWith3(list);
        duplicateWith7(list);
    }

    cout << "Результат:\n";
    printList(list);

    clearList(list);
    return 0;
}
    