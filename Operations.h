#pragma once

class Expression
{
private:
    const int priority;

public:
    Expression(int p) : priority(p) {};
    int getPriority() const;
    virtual bool isNumber() const = 0;
    virtual ~Expression() = default;
};

class Number : public Expression
{
private:
    float value;

public:
    Number(float v) : Expression(-1), value(v) {};
    float getValue() const;
    bool isNumber() const override;
};

class Operation : public Expression
{
public:
    bool isNumber() const override;
    Operation(int p) : Expression(p) {};
    virtual float return_value(float left, float right) const = 0;
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

class Parentheses : public Expression
{
private:
    ParenthesesType type;

public:
    Parentheses(ParenthesesType t) : Expression(0), type(t) {};
    ParenthesesType getParenthesesType() const;
    bool isNumber() const override;
};
