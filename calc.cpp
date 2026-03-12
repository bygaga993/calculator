#include "calc.h"
#include<cmath>


const std::unique_ptr<Operation>& Calculator::GetOperationByName(std::string name) const{
    auto it = registry.find(name);
    if (it == registry.end()) {
        throw std::runtime_error("no such operation");
    }
    return it->second;
}

const std::map<std::string, std::unique_ptr<Operation>>& Calculator::GetOperatorsMap() const{
    return registry;
}