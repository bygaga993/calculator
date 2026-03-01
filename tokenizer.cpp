#include "tokenizer.h"
#include<memory>
#include<string>
#include<iostream>


float NumberExpr::getNumber() const{
    return value;
};

OperationType OperatorExpr::getType() const{ 
    return type;
}

void NumberExpr::Print() const {
    std::cout << value;
}

void OperatorExpr::Print() const {
    switch (type){
        case Plus: std::cout << '+'; break;
        case Minus: std::cout << '-'; break;
        case Mul: std::cout << '*'; break;
        case Div: std::cout << '/'; break;
        case LParen: std::cout << '('; break;
        case RParen: std::cout << ')'; break;
    }
}

bool NumberExpr::IsNumber() const{
    return true;
}

bool OperatorExpr::IsNumber() const{
    return false;
}

std::vector<std::unique_ptr<Expr>> Tokenizer::ToExprTokens() const {
    std::vector<std::unique_ptr<Expr>> tokens;

    for (size_t i = 0; i < expression.size(); ) {  

        if (std::isspace(expression[i])) {
            i++;
            continue;
        }

        if (std::isdigit(expression[i]) || expression[i] == '.') {
            std::string number;

            while (i < expression.size() &&
                  (std::isdigit(expression[i]) || expression[i] == '.')) {
                number += expression[i];
                i++;
            }

            float value = std::stof(number);
            tokens.push_back(std::make_unique<NumberExpr>(value));
        }
        else if (expression[i] == '+') {
            tokens.push_back(std::make_unique<OperatorExpr>(Plus));
            i++;
        }
        else if (expression[i] == '-') {
            tokens.push_back(std::make_unique<OperatorExpr>(Minus));
            i++;
        }
        else if (expression[i] == '*') {
            tokens.push_back(std::make_unique<OperatorExpr>(Mul));
            i++;
        }
        else if (expression[i] == '/') {
            tokens.push_back(std::make_unique<OperatorExpr>(Div));
            i++;
        }
        else if (expression[i] == '(') {
            tokens.push_back(std::make_unique<OperatorExpr>(LParen));
            i++;
        }
        else if (expression[i] == ')') {
            tokens.push_back(std::make_unique<OperatorExpr>(RParen));
            i++;
        }
        else if (expression[i] == '=') {
            break;
        }
        else {
            throw std::runtime_error("Unknown character");
        }
    }

    return tokens;
}