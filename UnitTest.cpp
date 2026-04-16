#include <gtest/gtest.h>
#include "Pay.h"

// 1. Тест ініціалізації та стандартних винятків (std::invalid_argument)
TEST(PayTestSuite, StandardExceptionTest) {
    Pay p;
    // Перевіряємо, чи кидається стандартний виняток при від'ємному окладі
    EXPECT_THROW(p.setFirst(-100.0), std::invalid_argument);

    p.setFirst(2500.0);
    EXPECT_DOUBLE_EQ(p.getFirst(), 2500.0);
}

// 2. Тест винятків-нащадків (MyException)
TEST(PayTestSuite, DerivedExceptionTest) {
    Pay p;
    // Перевіряємо наш власний клас MyException
    EXPECT_THROW(p.setSecond(-5), MyException);

    p.setSecond(20);
    EXPECT_EQ(p.getSecond(), 20);
}

// 3. Тест логіки інкрементів (first ++ vs second ++)
TEST(PayTestSuite, IncrementLogicTest) {
    Pay p(1000.0, 10);

    ++p; // префіксний має змінювати first
    EXPECT_DOUBLE_EQ(p.getFirst(), 1001.0);

    p++; // постфіксний має змінювати second
    EXPECT_EQ(p.getSecond(), 11);
}

// 4. Тест розрахунку суми та власного винятку (CustomError)
TEST(PayTestSuite, CalculationAndCustomErrorTest) {
    Pay p(2200.0, 11);

    // Розрахунок: (2200 / 22) * 11 = 1100
    EXPECT_DOUBLE_EQ(p.summa(22), 1100.0);

    // Перевірка власного винятку при 0 робочих днів
    EXPECT_THROW(p.summa(0), CustomError);
}

// Функція main не потрібна, її надасть gtest_main