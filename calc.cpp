#include "calc.h"
#include<cmath>

float AddOperation::change_value(float left, float right) const{
    return left + right;
}

float SubOperation::change_value(float left, float right) const{
    return left - right;
}

float MulOperation::change_value(float left, float right) const{
    return left * right;
}

float DivOperation::change_value(float left, float right) const{
    return left / right;
}


const std::unique_ptr<Operation>& Calculator::GetOperationByName(OperatorExpr name) const{
    auto it = registry.find(name);
    if (it == registry.end()) {
        throw std::runtime_error("no such operation");
    }
    return it->second;
}

const std::map<OperatorExpr, std::unique_ptr<Operation>>& Calculator::GetOperatorsMap() const{
    return registry;
}