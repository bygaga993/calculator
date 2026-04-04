cmake_minimum_required(VERSION 3.10)
project(Calculator VERSION 1.0.0)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Название исполняемого файла
set(TARGET_NAME calculator)

option(BUILD_TESTS "Build tests only" OFF)

# Исходные файлы
set(SOURCES
    src/calc.cpp
    src/ExpressionParser.cpp
    main.cpp
    src/Operations.cpp
    src/main_func.cpp
)

# Заголовочные файлы
set(HEADERS
    include/calc.h
    include/main_func.h
    include/ExpressionParser.h
    include/Operations.h
)

# Создание исполняемого файла
add_executable(${TARGET_NAME} ${SOURCES} ${HEADERS})

# Включение текущей директории для заголовочных файлов
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Опции компиляции
target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -pedantic)

# Режимы сборки
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Опционально: если используете санитайзеры для отладки
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${TARGET_NAME} PRIVATE -fsanitize=address -fsanitize=undefined)
    target_link_options(${TARGET_NAME} PRIVATE -fsanitize=address -fsanitize=undefined)
endif()

# подключаем тесты
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(third_party/gtest)
    add_subdirectory(tests)
endif()
