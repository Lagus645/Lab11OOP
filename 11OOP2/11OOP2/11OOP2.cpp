#include <iostream>
#include <deque>
#include <algorithm>
#include <numeric>
#include <clocale>
#include "Money.h"

using namespace std;

typedef deque<Money> MoneyDeque;

MoneyDeque make_money_deque(int n) {
    MoneyDeque md;
    for (int i = 0; i < n; i++) {
        Money m(rand() % 100, rand() % 100);
        md.push_back(m);
    }
    return md;
}

void print_money_deque(const MoneyDeque& md) {
    int i = 0;
    for (const auto& m : md) {
        cout << "[" << i++ << "] " << m << endl;
    }
    cout << endl;
}

Money find_max_money(const MoneyDeque& md) {
    return *max_element(md.begin(), md.end(),
        [](const Money& a, const Money& b) {
            return (a.get_rubles() < b.get_rubles()) ||
                (a.get_rubles() == b.get_rubles() && a.get_kopecks() < b.get_kopecks());
        });
}


void add_max_to_end(MoneyDeque& md) {
    Money max_val = find_max_money(md);
    md.push_back(max_val);
}

void remove_by_position(MoneyDeque& md, int pos) {
    if (pos < 0 || pos >= md.size()) {
        throw out_of_range("Некорректная позиция для удаления");
    }
    auto it = md.begin();
    advance(it, pos);
    md.erase(it);
}

Money calculate_average(const MoneyDeque& md) {
    if (md.empty()) return Money();
    Money sum = accumulate(md.begin(), md.end(), Money(),
        [](const Money& a, const Money& b) { return a + b; });
    return sum / md.size();
}

void add_average_to_each(MoneyDeque& md) {
    Money avg = calculate_average(md);
    for (auto& m : md) {
        m = m + avg;
    }
}

int main() {
    setlocale(LC_ALL, "russian");
    try {
        MoneyDeque md = make_money_deque(5);
        cout << "Исходный deque:" << endl;
        print_money_deque(md);

        add_max_to_end(md);
        cout << "После добавления максимума в конец:" << endl;
        print_money_deque(md);

        cout << "Введите номер элемента для удаления (0-" << md.size() - 1 << "): ";
        int pos;
        cin >> pos;

        remove_by_position(md, pos);
        cout << "После удаления элемента [" << pos << "]:" << endl;
        print_money_deque(md);

        add_average_to_each(md);
        cout << "После добавления среднего к каждому элементу:" << endl;
        print_money_deque(md);

    }
    catch (const out_of_range& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
    catch (...) {
        cerr << "Произошла неизвестная ошибка!" << endl;
    }
    return 0;
}