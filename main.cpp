#include <iostream>
#include <vector>
#include <memory>
#include <stack>
#include <string>

#include "calc.h"
#include "ExpressionParser.h"
#include "Operations.h"
#include "main_func.h"


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