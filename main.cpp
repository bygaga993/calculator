#include <iostream>
#include <vector>
#include <memory>
#include <stack>
#include <string>

#include "include/calc.h"
#include "include/ExpressionParser.h"
#include "include/Operations.h"
#include "include/main_func.h"


int main()
{
    Calculator calc;
    calc.RegisterOperation<AddOperation>("+").RegisterOperation<SubOperation>("-").RegisterOperation<DivOperation>("/").RegisterOperation<MulOperation>("*");

    std::cout << "Введите выражение \n";
    std::string s;
    std::getline(std::cin, s);

    ExpressionParser expression(calc);
    expression.Parse(s);

    auto NumTokens = expression.getNumTokens();
    auto OpTokens = expression.getOpTokens();
    auto OrderTokens = expression.getOrderTokens();

    std::cout << getResult(OpTokens, NumTokens, OrderTokens);
    return 0;
}