#pragma once
#include <iostream>
using namespace std;

class Money {
    long rubles;
    int kopecks;
public:
    Money() : rubles(0), kopecks(0) {}
    Money(long r, int k) : rubles(r), kopecks(k) {
        normalize();
    }
    Money(const Money& m) : rubles(m.rubles), kopecks(m.kopecks) {}

    void normalize() {
        rubles += kopecks / 100;
        kopecks %= 100;
    }

    long get_rubles() const { return rubles; }
    int get_kopecks() const { return kopecks; }
    void set_rubles(long r) { rubles = r; }
    void set_kopecks(int k) { kopecks = k; normalize(); }

    Money operator+(const Money&) const;
    Money operator/(int) const;
    bool operator>(const Money&) const;
    bool operator<(const Money&) const;
    bool operator==(const Money&) const;

    friend istream& operator>>(istream& in, Money& m);
    friend ostream& operator<<(ostream& out, const Money& m);
}; 
