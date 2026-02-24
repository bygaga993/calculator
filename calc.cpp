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


template <class T>
Calculator& Calculator::RegisterOperation(std::string name) noexcept {
            registry.emplace(std::move(name), std::make_unique<T>());
            return *this;
}

const std::unique_ptr<Operation>& Calculator::GetOperationByName(std::string name) const {
    auto it = registry.find(name);  
    
    if (it == registry.end())  
        throw std::runtime_error("no such operation: " + name);
    
    return it->second;  
}