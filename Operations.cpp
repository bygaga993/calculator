#include "Operations.h"
#include<memory>


int Expression::getPriority() const {
    return priority;
}

bool Number::isNumber() const {
    return true;
}

bool Operation::isNumber() const{
    return false;
}


float AddOperation::return_value(float left, float right) const{
    return left + right;
}

float SubOperation::return_value(float left, float right) const{
    return left - right;
}

float MulOperation::return_value(float left, float right) const{
    return left * right;
}

float DivOperation::return_value(float left, float right) const{
    return left / right;
}

bool Parentheses::isNumber() const{
    return false;
}

ParenthesesType Parentheses::getParenthesesType() const{
    return type;
}

float Number::return_value(float, float) const{
    return value;
}


float Parentheses::return_value(float, float) const{
        throw std::runtime_error("Parentheses cannot be evaluated directly");
}