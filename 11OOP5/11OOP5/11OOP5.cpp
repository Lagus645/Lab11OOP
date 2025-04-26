#include "Vector.h"
#include <iostream>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, "russian");
    try {
        int n;
        cout << "Введите количество элементов: ";
        cin >> n;

        Vector<Money> vm(n);

        cout << "\nИсходный стек:\n";
        vm.print();

        vm.addMax();
        cout << "\nПосле добавления максимума:\n";
        vm.print();

        size_t pos;
        cout << "\nВведите позицию для удаления (0-" << vm.size() - 1 << "): ";
        cin >> pos;
        vm.removeAt(pos);
        cout << "После удаления:\n";
        vm.print();

        vm.addAverage();
        cout << "\nПосле добавления среднего:\n";
        vm.print();

    }
    catch (const std::exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    return 0;
}