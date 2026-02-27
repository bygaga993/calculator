#include "calc.h"
#include<cmath>

float Add::change_value(float left, float right) const{
    return left + right;
}

float Sub::change_value(float left, float right) const{
    return left - right;
}

float Mul::change_value(float left, float right) const{
    return left * right;
}

float Div::change_value(float left, float right) const{
    return left / right;
}

float Pow::change_value(float left, float right) const{
    return pow(left, right);
}


const std::unique_ptr<Operation>& Calculator::GetOperationByName(std::string name) const{
    auto it = registry.find(name);
    if (it == registry.end()) {
        throw std::runtime_error("no such operation");
    }
    return it->second;
}