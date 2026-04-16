cmake_minimum_required(VERSION 3.14)
project(PayProject CXX)

# Встановлюємо стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- ПІДКЛЮЧЕННЯ GOOGLE TEST ---
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# Для Windows: запобігання помилкам з перевизначенням рантайму
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- ОСНОВНА ПРОГРАМА (Лабораторна) ---
add_executable(PayApp main.cpp Pay.cpp Pay.h)

# --- UNIT TESTS (Google Test) ---
# Створюємо окремий файл для тестів
add_executable(UnitTest UnitTest.cpp Pay.cpp Pay.h)

# Підключаємо бібліотеки GTest
# gtest_main автоматично додає функцію main() для тестів
target_link_libraries(UnitTest GTest::gtest_main)

# Дозволяємо CMake бачити ці тести
include(GoogleTest)
gtest_discover_tests(UnitTest)