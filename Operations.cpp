#include "Operations.h"
#include "ExpressionParser.h"

#include <memory>
#include <stack>
#include <stdexcept>

int Expression::getPriority() const
{
    return priority;
}

bool Number::isNumber() const
{
    return true;
}

bool Operation::isNumber() const
{
    return false;
}

float AddOperation::return_value(float left, float right) const
{
    return left + right;
}

float SubOperation::return_value(float left, float right) const
{
    return left - right;
}

float MulOperation::return_value(float left, float right) const
{
    return left * right;
}

float DivOperation::return_value(float left, float right) const
{
    if (right == 0){
        throw std::runtime_error("деление на ноль невозможно");
    }
    return left / right;
}

bool Parentheses::isNumber() const
{
    return false;
}

ParenthesesType Parentheses::getParenthesesType() const
{
    return type;
}

float Number::getValue() const
{
    return value;
}


void Number::process(
    std::vector<std::shared_ptr<Operation>>& postfixExpr,
    std::vector<std::shared_ptr<Number>>& postfixNumbers,
    std::vector<std::shared_ptr<Expression>>& postfixTokens,
    std::stack<std::shared_ptr<Expression>>&
) {
    appendToPostfix(postfixExpr, postfixNumbers, postfixTokens);
}


void Number::appendToPostfix(
    std::vector<std::shared_ptr<Operation>>&,
    std::vector<std::shared_ptr<Number>>& postfixNumbers,
    std::vector<std::shared_ptr<Expression>>& postfixTokens
) {
    auto self = shared_from_this();
    postfixNumbers.push_back(self);
    postfixTokens.push_back(self);
}

void Operation::process(
    std::vector<std::shared_ptr<Operation>>& postfixExpr,
    std::vector<std::shared_ptr<Number>>& postfixNumbers,
    std::vector<std::shared_ptr<Expression>>& postfixTokens,
    std::stack<std::shared_ptr<Expression>>& opStack
) {
    while (!opStack.empty() && opStack.top()->getPriority() > 0) {
        if (opStack.top()->getPriority() >= this->getPriority()) {
            opStack.top()->appendToPostfix(postfixExpr, postfixNumbers, postfixTokens);
            opStack.pop();
        } else {
            break;
        }
    }
    opStack.push(shared_from_this());
}

void Operation::appendToPostfix(
    std::vector<std::shared_ptr<Operation>>& postfixExpr,
    std::vector<std::shared_ptr<Number>>&,
    std::vector<std::shared_ptr<Expression>>& postfixTokens
) {
    auto self = shared_from_this();
    postfixExpr.push_back(self);
    postfixTokens.push_back(self);
}


void Parentheses::process(
    std::vector<std::shared_ptr<Operation>>& postfixExpr,
    std::vector<std::shared_ptr<Number>>& postfixNumbers,
    std::vector<std::shared_ptr<Expression>>& postfixTokens,
    std::stack<std::shared_ptr<Expression>>& opStack
) {
    if (type == LParen){
        opStack.push(shared_from_this());
        return;
    } else {
        while (!opStack.empty()){
            auto topToken = opStack.top();
            opStack.pop();
            if (topToken -> getPriority() == 0){
                break;
            }
            topToken->appendToPostfix(postfixExpr, postfixNumbers, postfixTokens);
        }
    }
}


void Parentheses::appendToPostfix(
    std::vector<std::shared_ptr<Operation>>&,
    std::vector<std::shared_ptr<Number>>&,
    std::vector<std::shared_ptr<Expression>>& 
) {
    throw std::logic_error("Parentheses cannot be added to postfix");
}