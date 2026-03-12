#include<string>
#include<vector>
#include<stack>
#include <memory>
#include <stdexcept>
#include <iostream>
#include "ExpressionParser.h"
#include "Operations.h"


bool ExpressionParser::ContainsOperation(std::string type) const{
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
            tokens.push_back(std::make_unique<Number>(value));
        }
        else if (expression[i] == '+' && ContainsOperation("+")) {
            tokens.push_back(std::make_unique<AddOperation>());
            i++;
        }
        else if (expression[i] == '-' && ContainsOperation("-")) {
            tokens.push_back(std::make_unique<SubOperation>());
            i++;
        }
        else if (expression[i] == '*' && ContainsOperation("*")) {
            tokens.push_back(std::make_unique<MulOperation>());
            i++;
        }
        else if (expression[i] == '/' && ContainsOperation("/")) {
            tokens.push_back(std::make_unique<DivOperation>());
            i++;
        }
        else if (expression[i] == '(') {
            tokens.push_back(std::make_unique<Parentheses>(LParen));
            i++;
        }
        else if (expression[i] == ')') {
            tokens.push_back(std::make_unique<Parentheses>(RParen));
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
    std::vector<std::unique_ptr<Expression>> postfixExpr;
    std::stack<std::unique_ptr<Expression>> opStack;

    for (auto& token : tokens)
    {
        if (token->isNumber())
        {
            postfixExpr.push_back(std::move(token));
            continue;
        }

        int priority = token->getPriority();

        if (priority == 0)
        {
            auto* paren = dynamic_cast<Parentheses*>(token.get());
            
            if (paren->getParenthesesType() == LParen)
            {
                opStack.push(std::move(token));
            }
            else 
            {
                while (!opStack.empty())
                {
                    auto topToken = std::move(opStack.top());
                    opStack.pop();

                    if (topToken->getPriority() == 0) 
                        break;

                    postfixExpr.push_back(std::move(topToken));
                }
            }
        }
        else
        {
            while (!opStack.empty() && opStack.top()->getPriority() > 0)
            {
                if (opStack.top()->getPriority() >= priority)
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

    while (!opStack.empty())
    {
        postfixExpr.push_back(std::move(opStack.top()));
        opStack.pop();
    }
    
    tokens = std::move(postfixExpr);
}



std::vector<std::unique_ptr<Expression>> ExpressionParser::getTokens(){
    return std::move(tokens);  
}