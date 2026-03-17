#include <iostream>
#include <vector>
#include <memory>
#include <stack>
#include <string>

#include "calc.h"
#include "ExpressionParser.h"
#include "Operations.h"

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

    std::stack<float> resultStack;
    size_t numberIndex = 0;
    size_t opIndex = 0;

    while (numberIndex < NumTokens.size() || opIndex < OpTokens.size())
    {
        if (numberIndex < NumTokens.size())
        {
            resultStack.push(NumTokens[numberIndex]->getValue());
            numberIndex++;
        }
        else
        {
            if (resultStack.size() < 2)
            {
                std::cout << "in result stack error";
                break;
            }

            float right = resultStack.top();
            resultStack.pop();
            float left = resultStack.top();
            resultStack.pop();

            float result = OpTokens[opIndex]->return_value(left, right);
            resultStack.push(result);
            opIndex++;
        }
    }

    std::cout << resultStack.top();
    return 0;
}