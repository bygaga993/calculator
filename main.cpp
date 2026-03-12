#include<iostream>
#include<vector>
#include <memory>
#include<string>
#include "calc.h"
#include "ExpressionParser.h"
#include "Operations.h"



int main() {
    Calculator calc;
    calc.RegisterOperation<AddOperation>("+").
        RegisterOperation<SubOperation>("-").
        RegisterOperation<DivOperation>("/").
        RegisterOperation<MulOperation>("*");


    std::cout << "Введите выражение \n";
    std::string s;
    std::getline(std::cin, s);

    ExpressionParser expression(calc);
    expression.Parse(s);
    expression.ToPostfix();

    auto tokens = expression.getTokens();

    std::stack<float> resultStack;
    for (auto& token: tokens){
        if (token->isNumber()){
            resultStack.push(token->return_value());
        } else {
            float result;
            auto right = resultStack.top(); 
            resultStack.pop();
            auto left = resultStack.top();  
            resultStack.pop();
            result = token->return_value(left, right);
            resultStack.push(result);
        }
    }
    std::cout << resultStack.top();
    return 0;
}