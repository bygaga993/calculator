cmake_minimum_required(VERSION 3.10)
project(Calc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Все .cpp файлы в текущей директории
set(SOURCES
    calc.cpp
    ExpressionParser.cpp
    main.cpp
    Expression.cpp
    # Добавьте другие .cpp файлы если есть
)

add_executable(calc ${SOURCES})

# Опционально: включить предупреждения
if(APPLE)
    target_compile_options(calc PRIVATE -Wall -Wextra -Wpedantic)
endif()