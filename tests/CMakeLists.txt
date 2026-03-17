set(TEST_TARGET calculator_tests)

add_executable(${TEST_TARGET}
    test_streq.cpp
    ../Operations.cpp
    ../ExpressionParser.cpp
    ../calc.cpp
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