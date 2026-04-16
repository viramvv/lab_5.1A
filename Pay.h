#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

// Власний виняток-нащадок
class MyException : public std::runtime_error {
public:
    MyException(const std::string& msg) : std::runtime_error(msg) {}
};

// Повністю власний тип винятку
class CustomError {
    std::string message;
public:
    CustomError(std::string msg) : message(msg) {}
    std::string what() const { return message; }
};

class Pay {
private:
    double first;
    int second;

public:
    // noexcept(false) замінює throw(...)
    Pay() noexcept;
    Pay(double f, int s) noexcept(false);
    Pay(const Pay& p) noexcept;

    void setFirst(double f) noexcept(false);
    void setSecond(int s) noexcept(false);

    double getFirst() const { return first; }
    int getSecond() const { return second; }

    bool Init(double f, int s);
    void Read();
    void Display() const;

    double summa(int workingDaysInMonth) const noexcept(false);

    // Операції
    Pay& operator=(const Pay& p);
    operator std::string() const;

    Pay& operator++();
    Pay operator++(int);
    Pay& operator--();
    Pay operator--(int);

    friend std::ostream& operator<<(std::ostream& out, const Pay& p);
    friend std::istream& operator>>(std::istream& in, Pay& p);
};

Pay makePay(double f, int s);