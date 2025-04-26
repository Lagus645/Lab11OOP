#pragma once
#include <stack>
#include <vector>
#include <algorithm>
#include "Money.h"

template<class T>
class Vector {
    std::stack<T> s;

    std::vector<T> toVector() const {
        std::vector<T> v;
        auto temp = s;
        while (!temp.empty()) {
            v.push_back(temp.top());
            temp.pop();
        }
        std::reverse(v.begin(), v.end());
        return v;
    }

    void fromVector(const std::vector<T>& v) {
        std::stack<T> newStack;
        for (const auto& item : v) {
            newStack.push(item);
        }
        s = newStack;
    }

public:
    Vector(int n) {
        for (int i = 0; i < n; ++i) {
            T item;
            std::cout << "Введите элемент " << i + 1 << " (формат: рубли,копейки): ";
            std::cin >> item;
            s.push(item);
        }
    }

    void print() const {
        auto v = toVector();
        for (size_t i = 0; i < v.size(); ++i) {
            std::cout << "[" << i << "] " << v[i] << "\n";
        }
    }

    T max() const {
        auto v = toVector();
        return *std::max_element(v.begin(), v.end());
    }

    void addMax() {
        s.push(max());
    }

    void removeAt(size_t pos) {
        auto v = toVector();
        if (pos >= v.size()) throw std::out_of_range("Invalid position");
        v.erase(v.begin() + pos);
        fromVector(v);
    }

    T average() const {
        auto v = toVector();
        T sum;
        for (const auto& item : v) {
            sum = sum + item;
        }
        return sum / v.size();
    }

    void addAverage() {
        auto v = toVector();
        T avg = average();
        for (auto& item : v) {
            item = item + avg;
        }
        fromVector(v);
    }

    size_t size() const { return s.size(); }
};