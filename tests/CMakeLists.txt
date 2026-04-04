set(TEST_TARGET calculator_tests)

add_executable(${TEST_TARGET}
    tests_operation.cpp
    tests_parser.cpp
    tests_calculate.cpp
    ../src/Operations.cpp
    ../src/ExpressionParser.cpp
    ../src/calc.cpp
    ../src/main_func.cpp
)

target_link_libraries(calculator_tests
    PRIVATE
    gtest
    gtest_main
)

target_compile_options(${TEST_TARGET}
    PRIVATE -Wall -Wextra -pedantic
)

add_test(NAME calculator_tests COMMAND calculator_tests)