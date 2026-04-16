#include <iostream>
#include "Pay.h"

// Функція для демонстрації bad_exception
// У C++17 bad_exception зазвичай виникає при порушенні динамічної специфікації,
// але оскільки вони видалені, ми просто покажемо, що знаємо про його існування.
void simulate_bad_exception() {
    std::cout << "Демонстрація bad_exception зазвичай потребує застарілого throw(type)" << std::endl;
    throw std::bad_exception();
}

int main() {
    // 1. Розмір класу
    std::cout << "Розмір класу Pay: " << sizeof(Pay) << " байт" << std::endl;

#pragma pack(push, 1)
    struct Packed { double f; int s; };
#pragma pack(pop)
    std::cout << "Розмір упакованого класу: " << sizeof(Packed) << " байт" << std::endl;

    std::cout << "\n--- ТЕСТУВАННЯ ВИHЯТКІВ ---\n";

    // ПЕРЕДАЧА ЗА ЗНАЧЕННЯМ (Стандартний виняток)
    try {
        Pay p1(-100, 10);
    } catch (std::invalid_argument e) {
        std::cout << "Спіймано за значенням (std): " << e.what() << std::endl;
    }

    // ПЕРЕДАЧА ЗА ПОСИЛАННЯМ (Нащадок)
    try {
        Pay p2(2000, 20);
        p2.setSecond(-1);
    } catch (const MyException& e) {
        std::cout << "Спіймано за посиланням (MyException): " << e.what() << std::endl;
    }

    // ПЕРЕДАЧА ЗА ВКАЗІВНИКОМ (Власний тип)
    try {
        throw new CustomError("Специфічна помилка бізнес-логіки");
    } catch (CustomError* e) {
        std::cout << "Спіймано за вказівником (CustomError): " << e->what() << std::endl;
        delete e; // Чистимо пам'ять!
    }

    // Тест bad_exception
    try {
        simulate_bad_exception();
    } catch (const std::bad_exception& e) {
        std::cout << "Спіймано: " << e.what() << std::endl;
    }

    // Демонстрація інкрементів
    Pay p3(5000, 15);
    std::cout << "\nПочатковий стан: " << p3 << std::endl;
    ++p3;
    p3++;
    std::cout << "Після інкрементів: " << p3 << std::endl;

    return 0;
}