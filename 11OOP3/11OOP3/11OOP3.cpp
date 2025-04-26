#include "Vector.h"
#include <iostream>
#include <clocale>

int main() {
    setlocale(LC_ALL, "russian");
    try {
        int n;
        std::cout << "Введите количество элементов: ";
        std::cin >> n;

        Vector<Money> vm(n);

        std::cout << "\nИсходный вектор:\n";
        vm.print();

        // 1. Добавить максимальный элемент в конец
        vm.addMaxToEnd();
        std::cout << "\nПосле добавления максимума в конец:\n";
        vm.print();

        // 2. Удалить элемент по позиции
        size_t pos;
        std::cout << "\nВведите позицию для удаления (0-" << vm.size() - 1 << "): ";
        std::cin >> pos;
        vm.removeAt(pos);
        std::cout << "После удаления элемента [" << pos << "]:\n";
        vm.print();

        // 3. Добавить среднее к каждому элементу
        vm.addAverageToEach();
        std::cout << "\nПосле добавления среднего к каждому элементу:\n";
        vm.print();

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}