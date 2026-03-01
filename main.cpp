#include<iostream>
#include<vector>
#include <memory>
#include<string>
#include "calc.h"
#include "ExpressionParser.h"
#include "tokenizer.h"



int main() {
    Calculator calc;
    calc.RegisterOperation<AddOperation>(OperatorExpr(Plus)).
        RegisterOperation<SubOperation>(OperatorExpr(Minus)).
        RegisterOperation<DivOperation>(OperatorExpr(Div)).
        RegisterOperation<MulOperation>(OperatorExpr(Mul));


    std::cout << "Введите выражение \n";
    std::string s;
    std::getline(std::cin, s);

    // преобразуем выражение в вектор токенов, потом преобразуем их в обратную польскую нотацию
    Tokenizer tok(s);
    ExpressionParser expression(tok.ToExprTokens());
    expression.ToPostfix();

    //получаем вектор где токены уже в правильном порядке и уже считаем результат
    auto tokens = expression.getTokens();
    std::stack<std::unique_ptr<Expr>> resultStack;
    for (auto& token: tokens){
        if (token->IsNumber()){
            resultStack.push(std::move(token));
        } else {
            float result;
            auto* op = dynamic_cast<OperatorExpr*>(token.get());
            OperationType opType = op->getType();
            auto right_ptr = std::move(resultStack.top()); 
            resultStack.pop();
            auto left_ptr = std::move(resultStack.top());  
            resultStack.pop();
            auto* right = dynamic_cast<NumberExpr*>(right_ptr.get());
            auto* left  = dynamic_cast<NumberExpr*>(left_ptr.get());
            result = calc.GetOperationByName(opType)->change_value(left->getNumber(), right->getNumber());
            resultStack.push(std::make_unique<NumberExpr>(result));
        }
    }
    
    auto* result = dynamic_cast<NumberExpr*>(resultStack.top().get());
    std::cout << result->getNumber();
    return 0;
}