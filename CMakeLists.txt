cmake_minimum_required(VERSION 3.14)

# Задаем используемый стандарт С++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(bigint-lab)

# Задаем имя исполняемого файла основной программы
set(exe_name ${PROJECT_NAME})

# Задаем имя исполняемого файла программы для запуска тестов
set(test_name test_${PROJECT_NAME})

# Включаем отслеживание всех предупреждений
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# Описываем основную библиотеку - только BigInt.cpp
add_library(corelib OBJECT src/BigInt.cpp)

# Подключаем заголовочные файлы для библиотеки
target_include_directories(corelib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Описываем исполняемый файл основной программы: main.cpp + основная библиотека
add_executable(${exe_name} src/main.cpp)
target_link_libraries(${exe_name} corelib)

# Подключаем заголовочные файлы для исполняемого файла
target_include_directories(${exe_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# ========== все, что ниже, относится к тестированию при помощи GoogleTest ==========

# Скачиваем библиотеку GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Описываем исполняемый файл программы для запуска тестов
add_executable(${test_name} tests/test_bigint.cpp)
target_link_libraries(${test_name} gtest_main corelib)

# Подключаем заголовочные файлы для тестов
target_include_directories(${test_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Добавляем возможность запускать тесты через "make test"
include(GoogleTest)
gtest_discover_tests(${test_name})