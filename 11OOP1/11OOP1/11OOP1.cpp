#include <iostream>
#include <deque>
#include <algorithm>
#include <numeric>
#include <clocale>

using namespace std;

typedef deque<int> Deque;

// Функция для формирования deque
Deque make_deque(int n) {
    Deque d;
    for (int i = 0; i < n; i++) {
        int a = rand() % 100 - 50;
        d.push_back(a);
    }
    return d;
}

// Функция для печати deque с нумерацией элементов
void print_deque(const Deque& d) {
    int i = 0;
    for (auto it = d.begin(); it != d.end(); ++it, ++i) {
        cout << "[" << i << "] " << *it << endl;
    }
    cout << endl;
}

// Найти максимальный элемент
int find_max(const Deque& d) {
    return *max_element(d.begin(), d.end());
}

// Добавить максимальный элемент в конец
void add_max_to_end(Deque& d) {
    int max_val = find_max(d);
    d.push_back(max_val);
}

// Удалить элемент по позиции
void remove_by_position(Deque& d, int pos) {
    if (pos < 0 || pos >= d.size()) {
        throw out_of_range("Некорректная позиция для удаления");
    }
    auto it = d.begin();
    advance(it, pos);
    d.erase(it);
}

// Вычислить среднее арифметическое
double calculate_average(const Deque& d) {
    if (d.empty()) return 0;
    return accumulate(d.begin(), d.end(), 0.0) / d.size();
}

// Добавить среднее к каждому элементу
void add_average_to_each(Deque& d) {
    double avg = calculate_average(d);
    for (auto& elem : d) {
        elem += avg;
    }
}

int main() {
    setlocale(LC_ALL, "russian");
    try {
        // Создаем deque
        Deque d = make_deque(10);
        cout << "Исходный deque:" << endl;
        print_deque(d);

        // 1. Добавляем максимальный элемент в конец
        add_max_to_end(d);
        cout << "После добавления максимума в конец:" << endl;
        print_deque(d);

        // 2. Удаление элемента по позиции
        cout << "Введите номер элемента для удаления (0-" << d.size() - 1 << "): ";
        int pos;
        cin >> pos;

        remove_by_position(d, pos);
        cout << "После удаления элемента [" << pos << "]:" << endl;
        print_deque(d);

        // 3. Добавляем среднее к каждому элементу
        add_average_to_each(d);
        cout << "После добавления среднего к каждому элементу:" << endl;
        print_deque(d);

    }
    catch (const out_of_range& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
    catch (...) {
        cerr << "Произошла неизвестная ошибка!" << endl;
    }

    return 0;
}