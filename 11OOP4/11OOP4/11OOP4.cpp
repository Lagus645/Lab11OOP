#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <numeric>
#include <clocale>
#include "Money.h"

using namespace std;

typedef stack<Money> MoneyStack;
typedef vector<Money> MoneyVector;

MoneyVector copy_stack_to_vector(MoneyStack s) {
    MoneyVector v;
    while (!s.empty()) {
        v.push_back(s.top());
        s.pop();
    }
    reverse(v.begin(), v.end());
    return v;
}

MoneyStack copy_vector_to_stack(MoneyVector v) {
    MoneyStack s;
    for (const auto& m : v) {
        s.push(m);
    }
    return s;
}

void print_stack(MoneyStack s) {
    MoneyVector v = copy_stack_to_vector(s);
    int i = 0;
    for (const auto& m : v) {
        cout << "[" << i++ << "] " << m << endl;
    }
    cout << endl;
}

Money find_max_money(MoneyStack s) {
    MoneyVector v = copy_stack_to_vector(s);
    if (v.empty()) {
        throw runtime_error("Стек пуст");
    }
    return *max_element(v.begin(), v.end());
}

void add_max_to_end(MoneyStack& s) {
    Money max_val = find_max_money(s);
    MoneyVector v = copy_stack_to_vector(s);
    v.push_back(max_val);
    s = copy_vector_to_stack(v);
}

void remove_by_position(MoneyStack& s, int pos) {
    MoneyVector v = copy_stack_to_vector(s);
    if (pos < 0 || pos >= v.size()) {
        throw out_of_range("Некорректная позиция для удаления");
    }
    v.erase(v.begin() + pos);
    s = copy_vector_to_stack(v);
}

Money calculate_average(MoneyStack s) {
    MoneyVector v = copy_stack_to_vector(s);
    if (v.empty()) return Money();
    Money sum = accumulate(v.begin(), v.end(), Money(),
        [](const Money& a, const Money& b) { return a + b; });
    return sum / v.size();
}

void add_average_to_each(MoneyStack& s) {
    Money avg = calculate_average(s);
    MoneyVector v = copy_stack_to_vector(s);
    for (auto& m : v) {
        m = m + avg;
    }
    s = copy_vector_to_stack(v);
}

int main() {
    setlocale(LC_ALL, "russian");
    try {
        MoneyStack ms;
        ms.push(Money(10, 50));
        ms.push(Money(20, 30));
        ms.push(Money(5, 10));

        cout << "Исходный стек:" << endl;
        print_stack(ms);

        add_max_to_end(ms);
        cout << "После добавления максимума в конец:" << endl;
        print_stack(ms);

        cout << "Введите номер элемента для удаления (0-" << copy_stack_to_vector(ms).size() - 1 << "): ";
        int pos;
        cin >> pos;

        remove_by_position(ms, pos);
        cout << "После удаления элемента [" << pos << "]:" << endl;
        print_stack(ms);

        add_average_to_each(ms);
        cout << "После добавления среднего к каждому элементу:" << endl;
        print_stack(ms);

    }
    catch (const out_of_range& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
    catch (...) {
        cerr << "Произошла неизвестная ошибка!" << endl;
    }
    return 0;
}