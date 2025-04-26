#ifndef MONEY_H
#define MONEY_H

#include <iostream>
#include <iomanip>
#include <stdexcept>

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
    Money() : rubles(0), kopecks(0) {}
    Money(long r, int k) : rubles(r), kopecks(k) { normalize(); }

    long getRubles() const { return rubles; }
    int getKopecks() const { return kopecks; }

    Money operator+(const Money& other) const {
        return Money(rubles + other.rubles, kopecks + other.kopecks);
    }

    Money operator/(int divisor) const {
        if (divisor == 0) throw std::invalid_argument("Division by zero");
        long total = rubles * 100 + kopecks;
        total /= divisor;
        return Money(total / 100, total % 100);
    }

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

    friend std::istream& operator>>(std::istream& in, Money& money) {
        char sep;
        in >> money.rubles >> sep >> money.kopecks;
        if (sep != ',') in.setstate(std::ios::failbit);
        money.normalize();
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const Money& money) {
        out << money.rubles << "," << std::setw(2) << std::setfill('0')
            << money.kopecks << " руб.";
        return out;
    }
};

#endif