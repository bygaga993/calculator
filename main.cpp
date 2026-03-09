#include<iostream>
#include<vector>
#include <memory>
#include<string>
#include "calc.h"
#include "ExpressionParser.h"



int main() {
    Calculator calc;
    calc.RegisterOperation<AddOperation>(OperatorExpr(Plus)).
        RegisterOperation<SubOperation>(OperatorExpr(Minus)).
        RegisterOperation<DivOperation>(OperatorExpr(Div)).
        RegisterOperation<MulOperation>(OperatorExpr(Mul));


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
            OperationType opType  = token->AsOperation();
            auto right = resultStack.top(); 
            resultStack.pop();
            auto left = resultStack.top();  
            resultStack.pop();
            result = calc.GetOperationByName(opType)->change_value(left, right);
            resultStack.push(result);
        }
    }
    std::cout << resultStack.top();
    return 0;
}