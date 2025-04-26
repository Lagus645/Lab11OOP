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
    // ����������� � ������ ���������
    Vector(int n) {
        data.reserve(n);
        for (int i = 0; i < n; ++i) {
            T item;
            std::cout << "������� ������� " << i + 1 << " (������: �����,�������): ";
            while (!(std::cin >> item)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "�������� ������! ������� ����� (�����,�������): ";
            }
            data.push_back(item);
        }
    }

    // ����� ���������
    void print() const {
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << "[" << i << "] " << data[i] << "\n";
        }
    }

    // ����� ������������ �������
    T findMax() const {
        if (data.empty()) throw std::runtime_error("������ ����");
        return *std::max_element(data.begin(), data.end());
    }

    // �������� ������������ ������� � �����
    void addMaxToEnd() {
        data.push_back(findMax());
    }

    // ������� ������� �� �������
    void removeAt(size_t pos) {
        if (pos >= data.size()) throw std::out_of_range("�������� �������");
        data.erase(data.begin() + pos);
    }

    // ��������� ������� ��������������
    T calculateAverage() const {
        if (data.empty()) return T();
        T sum = std::accumulate(data.begin(), data.end(), T());
        return sum / data.size();
    }

    // �������� ������� � ������� ��������
    void addAverageToEach() {
        T avg = calculateAverage();
        for (auto& item : data) {
            item = item + avg;
        }
    }

    size_t size() const { return data.size(); }
};