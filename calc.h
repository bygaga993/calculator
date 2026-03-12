#pragma once

#include<map>
#include<memory>
#include<string>

#include "Operations.h"


class Calculator{
    private:
        std::map<std::string, std::unique_ptr<Operation>> registry;
    
    public:
        Calculator() {};
        template <class T> 
        Calculator& RegisterOperation(std::string name) noexcept {
            registry.emplace(std::move(name), std::make_unique<T>());
            return *this;
        }
        const std::unique_ptr<Operation>& GetOperationByName(std::string name) const;
        const std::map<std::string, std::unique_ptr<Operation>>& GetOperatorsMap() const;
};