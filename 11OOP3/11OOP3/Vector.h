#pragma once
#include <vector>
#include <algorithm>
#include <numeric>
#include "Money.h"

template<class T>
class Vector {
private:
    std::vector<T> data;

public:
    // Конструктор с вводом элементов
    Vector(int n) {
        data.reserve(n);
        for (int i = 0; i < n; ++i) {
            T item;
            std::cout << "Введите элемент " << i + 1 << " (формат: рубли,копейки): ";
            while (!(std::cin >> item)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Неверный формат! Введите снова (рубли,копейки): ";
            }
            data.push_back(item);
        }
    }

    // Вывод элементов
    void print() const {
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << "[" << i << "] " << data[i] << "\n";
        }
    }

    // Найти максимальный элемент
    T findMax() const {
        if (data.empty()) throw std::runtime_error("Вектор пуст");
        return *std::max_element(data.begin(), data.end());
    }

    // Добавить максимальный элемент в конец
    void addMaxToEnd() {
        data.push_back(findMax());
    }

    // Удалить элемент по позиции
    void removeAt(size_t pos) {
        if (pos >= data.size()) throw std::out_of_range("Неверная позиция");
        data.erase(data.begin() + pos);
    }

    // Вычислить среднее арифметическое
    T calculateAverage() const {
        if (data.empty()) return T();
        T sum = std::accumulate(data.begin(), data.end(), T());
        return sum / data.size();
    }

    // Добавить среднее к каждому элементу
    void addAverageToEach() {
        T avg = calculateAverage();
        for (auto& item : data) {
            item = item + avg;
        }
    }

    size_t size() const { return data.size(); }
};