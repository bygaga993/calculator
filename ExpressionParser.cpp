#include<string>
#include<vector>
#include<stack>
#include <memory>
#include <stdexcept>
#include <iostream>
#include "tokenizer.h"
#include "ExpressionParser.h"


void ExpressionParser::ToPostfix()
{
    std::vector<std::unique_ptr<Expr>> postfixExpr;
    std::stack<std::unique_ptr<Expr>> opStack;

    auto getPrecedence = [](OperatorExpr* op) -> int {
        switch (op->getType()) {
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
            auto* op = dynamic_cast<OperatorExpr*>(token.get());
            OperationType opType = op->getType();
            
            if (opType == LParen)
            {
                opStack.push(std::move(token));
            } 
            else if (opType == RParen) 
            {
                while (!opStack.empty()) 
                {
                    auto* opTop = dynamic_cast<OperatorExpr*>(opStack.top().get());
                    
                    if (opTop->getType() == LParen)
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
                    auto* opTop = dynamic_cast<OperatorExpr*>(opStack.top().get());
                    
                    if (opTop->getType() == LParen) {
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