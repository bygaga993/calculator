#include<string>
#include<vector>
#include<stack>
#include <memory>
#include <stdexcept>
#include <iostream>
#include "tokenizer.h"
#include "ExpressionParser.h"


bool ExpressionParser::ContainsOperation(OperationType type) const{
    auto it = operators_.find(type);
    if (it != operators_.end()){
        return true;
    }
    return false;
}


void ExpressionParser::Parse(std::string expression){

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
        else if (expression[i] == '+' && ContainsOperation(Plus)) {
            tokens.push_back(std::make_unique<OperatorExpr>(Plus));
            i++;
        }
        else if (expression[i] == '-' && ContainsOperation(Minus)) {
            tokens.push_back(std::make_unique<OperatorExpr>(Minus));
            i++;
        }
        else if (expression[i] == '*' && ContainsOperation(Mul)) {
            tokens.push_back(std::make_unique<OperatorExpr>(Mul));
            i++;
        }
        else if (expression[i] == '/' && ContainsOperation(Div)) {
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
}

void ExpressionParser::ToPostfix()
{
    std::vector<std::unique_ptr<Expr>> postfixExpr;
    std::stack<std::unique_ptr<Expr>> opStack;

    auto getPrecedence = [](OperationType op) -> int {
        switch (op) {
            case Mul: case Div: return 2;
            case Plus: case Minus: return 1;
            case LParen: case RParen: return 0;
            default: return -1;
        }
    };

    for (auto& token : tokens)
    {
        if (token->IsNumber())
        {
            postfixExpr.push_back(std::move(token));
        } 
        else 
        {
            auto op = token->AsOperation();
            
            if (op == LParen)
            {
                opStack.push(std::move(token));
            } 
            else if (op == RParen) 
            {
                while (!opStack.empty()) 
                {
                    auto opTop = opStack.top()->AsOperation();
                    
                    if (opTop == LParen)
                    {
                        opStack.pop();
                        break;
                    }
                    
                    postfixExpr.push_back(std::move(opStack.top()));
                    opStack.pop();
                }
            } 
            else 
            {
                while (!opStack.empty()) 
                {
                    auto opTop = opStack.top()->AsOperation();
                    
                    if (opTop == LParen) {
                        break;
                    }
                    
                    if (getPrecedence(opTop) >= getPrecedence(op))
                    {
                        postfixExpr.push_back(std::move(opStack.top()));
                        opStack.pop();
                    } 
                    else 
                    {
                        break;
                    }
                }
                opStack.push(std::move(token));
            }
        }
    }

    while (!opStack.empty())
    {
        postfixExpr.push_back(std::move(opStack.top()));
        opStack.pop();
    }
    
    tokens = std::move(postfixExpr);
}

void ExpressionParser::Print() const{
    for (auto& token : tokens) {
        token->Print();
        std::cout << " ";
    }
    std::cout <<'\n';
}


std::vector<std::unique_ptr<Expr>> ExpressionParser::getTokens() {
    return std::move(tokens);  
}