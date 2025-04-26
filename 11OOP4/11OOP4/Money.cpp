#include "money.h"

Money Money::operator+(const Money& m) const {
    return Money(rubles + m.rubles, kopecks + m.kopecks);
}

Money Money::operator/(int n) const {
    if (n == 0) throw invalid_argument("Division by zero");
    long total_kopecks = rubles * 100 + kopecks;
    total_kopecks /= n;
    return Money(total_kopecks / 100, total_kopecks % 100);
}

bool Money::operator>(const Money& m) const {
    return (rubles > m.rubles) || (rubles == m.rubles && kopecks > m.kopecks);
}

bool Money::operator<(const Money& m) const {
    return (rubles < m.rubles) || (rubles == m.rubles && kopecks < m.kopecks);
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