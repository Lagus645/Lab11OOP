// Money.cpp
#include "Money.h"

Money Money::operator+(const Money& m) const {
    return Money(rubles + m.rubles, kopecks + m.kopecks);
}

Money Money::operator/(int n) const {
    long total_kopecks = rubles * 100 + kopecks;
    total_kopecks /= n;
    return Money(total_kopecks / 100, total_kopecks % 100);
}

bool Money::operator>(const Money& m) const {
    if (rubles > m.rubles) return true;
    if (rubles == m.rubles && kopecks > m.kopecks) return true;
    return false;
}

bool Money::operator==(const Money& m) const {
    return rubles == m.rubles && kopecks == m.kopecks;
}

istream& operator>>(istream& in, Money& m) {
    cout << "Rubles: "; in >> m.rubles;
    cout << "Kopecks: "; in >> m.kopecks;
    m.normalize();
    return in;
}

ostream& operator<<(ostream& out, const Money& m) {
    out << m.rubles << " rub. " << m.kopecks << " kop.";
    return out;
}