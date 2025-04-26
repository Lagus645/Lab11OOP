#ifndef MONEY_H
#define MONEY_H

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <sstream>

class Money {
private:
    long rubles;
    int kopecks;

    void normalize() {
        rubles += kopecks / 100;
        kopecks %= 100;
        if (kopecks < 0) {
            rubles--;
            kopecks += 100;
        }
    }

public:
    // Конструкторы
    Money() : rubles(0), kopecks(0) {}
    Money(long r, int k) : rubles(r), kopecks(k) { normalize(); }

    // Геттеры
    long getRubles() const { return rubles; }
    int getKopecks() const { return kopecks; }

    // Арифметические операции
    Money operator+(const Money& other) const {
        return Money(rubles + other.rubles, kopecks + other.kopecks);
    }

    Money operator/(int divisor) const {
        if (divisor == 0) throw std::invalid_argument("Деление на ноль");
        long total = rubles * 100 + kopecks;
        total /= divisor;
        return Money(total / 100, total % 100);
    }

    // Операторы сравнения
    bool operator>(const Money& other) const {
        return (rubles > other.rubles) ||
            (rubles == other.rubles && kopecks > other.kopecks);
    }

    bool operator<(const Money& other) const {
        return (rubles < other.rubles) ||
            (rubles == other.rubles && kopecks < other.kopecks);
    }

    bool operator==(const Money& other) const {
        return rubles == other.rubles && kopecks == other.kopecks;
    }

    // Ввод/вывод
    friend std::istream& operator>>(std::istream& in, Money& money) {
        std::string input;
        in >> input;

        size_t comma_pos = input.find(',');
        if (comma_pos == std::string::npos) {
            in.setstate(std::ios::failbit);
            return in;
        }

        try {
            money.rubles = std::stol(input.substr(0, comma_pos));
            money.kopecks = std::stoi(input.substr(comma_pos + 1));
        }
        catch (...) {
            in.setstate(std::ios::failbit);
            return in;
        }

        money.normalize();
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const Money& money) {
        out << money.rubles << "," << std::setw(2) << std::setfill('0')
            << money.kopecks << " руб.";
        return out;
    }
};

#endif // MONEY_H