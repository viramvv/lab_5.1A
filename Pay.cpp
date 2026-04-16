#include "Pay.h"
#include <sstream>


Pay::Pay() noexcept : first(0), second(0) {}

Pay::Pay(double f, int s) noexcept(false) {
    if (!Init(f, s)) {
        throw std::invalid_argument("Некоректні аргументи в конструкторі");
    }
}

Pay::Pay(const Pay& p) noexcept : first(p.first), second(p.second) {}


bool Pay::Init(double f, int s) {
    if (f >= 0 && s >= 0) {
        first = f;
        second = s;
        return true;
    }
    return false;
}

void Pay::setFirst(double f) noexcept(false) {
    if (f < 0) throw std::invalid_argument("Оклад від'ємний");
    first = f;
}

void Pay::setSecond(int s) noexcept(false) {
    if (s < 0) throw MyException("Дні від'ємні");
    second = s;
}

// Бізнес-логіка: розрахунок зарплати.
// Демонструє використання власного винятку (CustomError).
double Pay::summa(int workingDays) const noexcept(false) {
    if (workingDays <= 0) throw CustomError("Робочі дні мають бути > 0");
    return (first / workingDays) * second;
}


Pay& Pay::operator=(const Pay& p) {
    if (this != &p) {
        first = p.first;
        second = p.second;
    }
    return *this;
}

// Приведення типу до рядка.
Pay::operator std::string() const {
    std::stringstream ss;
    ss << "Оклад: " << first << ", Відпрацьовано днів: " << second;
    return ss.str();
}

Pay& Pay::operator++() {
    first++;
    return *this;
}


// Повертає копію об'єкта ДО змін.
Pay Pay::operator++(int) {
    Pay tmp = *this;
    second++;
    return tmp;
}

Pay& Pay::operator--() {
    first--;
    return *this;
}

Pay Pay::operator--(int) {
    Pay tmp = *this;
    second--;
    return tmp;
}

// Дружній оператор виводу у потік (cout << p).
std::ostream& operator<<(std::ostream& out, const Pay& p) {
    out << (std::string)p;
    return out;
}

// Дружній оператор введення (cin >> p).
// Якщо введені дані некоректні — кидає виняток, щоб програма не працювала з "бідою".
std::istream& operator>>(std::istream& in, Pay& p) {
    double f; int s;
    std::cout << "First (оклад): "; in >> f;
    std::cout << "Second (дні): "; in >> s;
    if (!p.Init(f, s)) throw std::invalid_argument("Помилка введення: дані не можуть бути від'ємними");
    return in;
}

Pay makePay(double f, int s) {
    if (f < 0 || s < 0) {
        std::cerr << "Критична помилка makePay: некоректні аргументи." << std::endl;
        exit(1); // Аварійне завершення
    }
    return Pay(f, s);
}