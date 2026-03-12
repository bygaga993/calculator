cmake_minimum_required(VERSION 3.10)
project(Calculator VERSION 1.0.0)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Название исполняемого файла
set(TARGET_NAME calculator)

# Исходные файлы
set(SOURCES
    calc.cpp
    ExpressionParser.cpp
    main.cpp
    Operations.cpp
)

# Заголовочные файлы
set(HEADERS
    calc.h
    ExpressionParser.h
    Operations.h
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