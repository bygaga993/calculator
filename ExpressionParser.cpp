#include <string>
#include <vector>
#include <stack>
#include <memory>
#include <stdexcept>
#include <iostream>
#include "ExpressionParser.h"
#include "Operations.h"

bool ExpressionParser::ContainsOperation(std::string type) const
{
    auto it = operators_.find(type);
    if (it != operators_.end())
    {
        return true;
    }
    return false;
}


bool isCorrectArithmeticExpression(const std::string& s) {
    int balance = 0;            
    bool expectOperand = true;   

    for (size_t i = 0; i < s.size();) {
        if (std::isspace(static_cast<unsigned char>(s[i]))) {
            ++i;
            continue;
        }

        if (expectOperand) {
            if (s[i] == '+' || s[i] == '-') {
                ++i;
                continue;
            }

            if (s[i] == '(') {
                ++balance;
                ++i;
                continue;
            }

            if (std::isdigit(static_cast<unsigned char>(s[i]))) {
                while (i < s.size() && std::isdigit(static_cast<unsigned char>(s[i]))) {
                    ++i;
                }
                expectOperand = false;
                continue;
            }

            return false;
        } else {
            if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
                expectOperand = true;
                ++i;
                continue;
            }

            if (s[i] == ')') {
                if (balance == 0) return false;
                --balance;
                ++i;
                continue;
            }

            return false;
        }
    }

    return !expectOperand && balance == 0;
}


void ExpressionParser::ToPostfix()
{

    std::vector<std::shared_ptr<Operation>> postfixExpr;
    std::vector<std::shared_ptr<Number>> postfixNumbers;
    std::vector<std::shared_ptr<Expression>> postfixTokens;


    std::stack<std::shared_ptr<Expression>> opStack;

   for (auto &token : tokens){
        token->process(postfixExpr, postfixNumbers, postfixTokens, opStack);
   }

    while (!opStack.empty())
    {
        opStack.top()->appendToPostfix(postfixExpr, postfixNumbers, postfixTokens);
        opStack.pop();
    }

    OpTokens = std::move(postfixExpr);
    NumTokens = std::move(postfixNumbers);
    OrderTokens = std::move(postfixTokens);
}

std::vector<std::shared_ptr<Operation>> ExpressionParser::getOpTokens()
{
    return std::move(OpTokens);
}

std::vector<std::shared_ptr<Number>> ExpressionParser::getNumTokens()
{
    return std::move(NumTokens);
}

std::vector<std::shared_ptr<Expression>> ExpressionParser::getOrderTokens()
{
    return OrderTokens;
}



void ExpressionParser::SkipSpaces(const std::string& expression, size_t& i)
{
    while (i < expression.size() &&
           std::isspace(static_cast<unsigned char>(expression[i])))
    {
        ++i;
    }
}

float ExpressionParser::ParseNumber(const std::string& expression, size_t& i, bool negative)
{
    std::string number;
    int dotCount = 0;

    if (negative)
        number += '-';

    while (i < expression.size())
    {
        unsigned char ch = static_cast<unsigned char>(expression[i]);

        if (std::isdigit(ch))
        {
            number += expression[i];
            ++i;
        }
        else if (expression[i] == '.')
        {
            ++dotCount;
            if (dotCount > 1)
                throw std::runtime_error("Invalid number format");

            number += expression[i];
            ++i;
        }
        else
        {
            break;
        }
    }

    if (number.empty() || number == "." || number == "-" || number == "-.")
        throw std::runtime_error("Invalid number format");

    return std::stof(number);
}



void ExpressionParser::Parse(std::string expression)
{
    tokens.clear();
    NumTokens.clear();
    OpTokens.clear();
    OrderTokens.clear();

    bool expectOperand = true;
    int parenBalance = 0;

    for (size_t i = 0; i < expression.size();)
    {
        SkipSpaces(expression, i);

        if (i >= expression.size())
            break;

        unsigned char ch = static_cast<unsigned char>(expression[i]);

        if (std::isdigit(ch) || expression[i] == '.')
        {
            if (!expectOperand)
                throw std::runtime_error("Expected operator before number");

            float value = ParseNumber(expression, i, false);
            tokens.push_back(std::make_shared<Number>(value));
            expectOperand = false;
            continue;
        }

        if (expression[i] == '(')
        {
            if (!expectOperand)
                throw std::runtime_error("Expected operator before '('");

            tokens.push_back(std::make_shared<Parentheses>(LParen));
            ++parenBalance;
            ++i;
            expectOperand = true;
            continue;
        }

        if (expression[i] == ')')
        {
            if (expectOperand)
                throw std::runtime_error("Unexpected ')'");

            if (parenBalance == 0)
                throw std::runtime_error("Unmatched ')'");

            tokens.push_back(std::make_shared<Parentheses>(RParen));
            --parenBalance;
            ++i;
            expectOperand = false;
            continue;
        }

        if (expression[i] == '+')
        {
            if (expectOperand)
            {
                size_t j = i + 1;
                SkipSpaces(expression, j);

                if (j >= expression.size())
                    throw std::runtime_error("Invalid use of unary '+'");

                if (std::isdigit(static_cast<unsigned char>(expression[j])) || expression[j] == '.')
                {
                    i = j;
                    float value = ParseNumber(expression, i, false);
                    tokens.push_back(std::make_shared<Number>(value));
                    expectOperand = false;
                    continue;
                }

                if (expression[j] == '(')
                {
                    if (!ContainsOperation("*"))
                        throw std::runtime_error("Operation '*' is not supported");
                    ++i; 
                    expectOperand = true;
                    continue;
                }

                throw std::runtime_error("Invalid use of unary '+'");
            }

            if (!ContainsOperation("+"))
                throw std::runtime_error("Operation '+' is not supported");

            tokens.push_back(std::make_shared<AddOperation>());
            ++i;
            expectOperand = true;
            continue;
        }

        if (expression[i] == '-')
        {
            if (expectOperand)
            {
                size_t j = i + 1;
                SkipSpaces(expression, j);

                if (j >= expression.size())
                    throw std::runtime_error("Invalid use of unary '-'");

                if (std::isdigit(static_cast<unsigned char>(expression[j])) || expression[j] == '.')
                {
                    i = j;
                    float value = ParseNumber(expression, i, true);
                    tokens.push_back(std::make_shared<Number>(value));
                    expectOperand = false;
                    continue;
                }

                if (expression[j] == '(')
                {
                    if (!ContainsOperation("*"))
                        throw std::runtime_error("Operation '*' is not supported");

                    tokens.push_back(std::make_shared<Number>(-1.0f));
                    tokens.push_back(std::make_shared<MulOperation>());
                    ++i; 
                    expectOperand = true;
                    continue;
                }

                throw std::runtime_error("Invalid use of unary '-'");
            }

            if (!ContainsOperation("-"))
                throw std::runtime_error("Operation '-' is not supported");

            tokens.push_back(std::make_shared<SubOperation>());
            ++i;
            expectOperand = true;
            continue;
        }

        if (expression[i] == '*')
        {
            if (expectOperand)
                throw std::runtime_error("Unexpected '*'");

            if (!ContainsOperation("*"))
                throw std::runtime_error("Operation '*' is not supported");

            tokens.push_back(std::make_shared<MulOperation>());
            ++i;
            expectOperand = true;
            continue;
        }

        if (expression[i] == '/')
        {
            if (expectOperand)
                throw std::runtime_error("Unexpected '/'");

            if (!ContainsOperation("/"))
                throw std::runtime_error("Operation '/' is not supported");

            tokens.push_back(std::make_shared<DivOperation>());
            ++i;
            expectOperand = true;
            continue;
        }

        if (expression[i] == '=')
            break;

        throw std::runtime_error("Unknown character");
    }

    if (parenBalance != 0)
        throw std::runtime_error("Unmatched '('");

    if (expectOperand)
        throw std::runtime_error("Expression ends unexpectedly");

    ToPostfix();
}