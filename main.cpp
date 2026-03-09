#include<iostream>
#include<vector>
#include <memory>
#include<string>
#include "calc.h"
#include "ExpressionParser.h"



int main() {
    Calculator calc;
    calc.RegisterOperation<AddOperation>(Plus).
        RegisterOperation<SubOperation>(Minus).
        RegisterOperation<DivOperation>(Div).
        RegisterOperation<MulOperation>(Mul);


    std::cout << "Введите выражение \n";
    std::string s;
    std::getline(std::cin, s);

    ExpressionParser expression(calc);
    expression.Parse(s);
    expression.ToPostfix();

    auto tokens = expression.getTokens();

    std::stack<float> resultStack;
    for (auto& token: tokens){
        if (token->IsNumber()){
            resultStack.push(token->AsNumber());
        } else {
            float result;
            auto right = resultStack.top(); 
            resultStack.pop();
            auto left = resultStack.top();  
            resultStack.pop();
            result = token->change_value(left, right);
            resultStack.push(result);
        }
    }
    std::cout << resultStack.top();
    return 0;
}