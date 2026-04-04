#pragma once
#include <vector>
#include <memory>
#include <stack>

class Operation;
class Number;
class Parentheses;

class Expression
{
private:
    const int priority;

public:
    Expression(int p) : priority(p) {};
    int getPriority() const;
    virtual bool isNumber() const = 0;

    virtual void process(std::vector<std::shared_ptr<Operation>>& postfixExpr,
    std::vector<std::shared_ptr<Number>>& postfixNumbers,
    std::vector<std::shared_ptr<Expression>>& postfixTokens,
    std::stack<std::shared_ptr<Expression>>& opStack
    ) = 0;

    virtual void appendToPostfix(
    std::vector<std::shared_ptr<Operation>>& postfixExpr,
    std::vector<std::shared_ptr<Number>>& postfixNumbers,
    std::vector<std::shared_ptr<Expression>>& postfixTokens
    ) = 0;

    virtual ~Expression() = default;
};

class Number : public Expression, 
                    public std::enable_shared_from_this<Number>
{
private:
    float value;

public:
    Number(float v) : Expression(-1), value(v) {};
    float getValue() const;
    bool isNumber() const override;

    void process(std::vector<std::shared_ptr<Operation>>& postfixExpr,
    std::vector<std::shared_ptr<Number>>& postfixNumbers,
    std::vector<std::shared_ptr<Expression>>& postfixTokens,
    std::stack<std::shared_ptr<Expression>>& opStack
    ) override;

    void appendToPostfix(
    std::vector<std::shared_ptr<Operation>>&,
    std::vector<std::shared_ptr<Number>>& postfixNumbers,
    std::vector<std::shared_ptr<Expression>>& postfixTokens
    ) override;

};

class Operation : public Expression, 
                    public std::enable_shared_from_this<Operation>
{
public:
    bool isNumber() const override;
    Operation(int p) : Expression(p) {};
    virtual float return_value(float left, float right) const = 0;

    void process(std::vector<std::shared_ptr<Operation>>& postfixExpr,
    std::vector<std::shared_ptr<Number>>& postfixNumbers,
    std::vector<std::shared_ptr<Expression>>& postfixTokens,
    std::stack<std::shared_ptr<Expression>>& opStack
    ) override;

    void appendToPostfix(
    std::vector<std::shared_ptr<Operation>>&,
    std::vector<std::shared_ptr<Number>>& postfixNumbers,
    std::vector<std::shared_ptr<Expression>>& postfixTokens
    ) override;
};

class AddOperation : public Operation
{
public:
    AddOperation() : Operation(1) {};
    float return_value(float left, float right) const override;
};

class SubOperation : public Operation
{
public:
    SubOperation() : Operation(1) {};
    float return_value(float left, float right) const override;
};

class MulOperation : public Operation
{
public:
    MulOperation() : Operation(2) {};
    float return_value(float left, float right) const override;
};

class DivOperation : public Operation
{
public:
    DivOperation() : Operation(2) {};
    float return_value(float left, float right) const override;
};

enum ParenthesesType
{
    RParen,
    LParen
};

class Parentheses : public Expression, 
            public std::enable_shared_from_this<Parentheses>
{
private:
    ParenthesesType type;

public:
    Parentheses(ParenthesesType t) : Expression(0), type(t) {};
    ParenthesesType getParenthesesType() const;
    bool isNumber() const override;

    void process(std::vector<std::shared_ptr<Operation>>& postfixExpr,
    std::vector<std::shared_ptr<Number>>& postfixNumbers,
    std::vector<std::shared_ptr<Expression>>& postfixTokens,
    std::stack<std::shared_ptr<Expression>>& opStack
    ) override;

    void appendToPostfix(
    std::vector<std::shared_ptr<Operation>>&,
    std::vector<std::shared_ptr<Number>>& postfixNumbers,
    std::vector<std::shared_ptr<Expression>>& postfixTokens
    ) override;
};