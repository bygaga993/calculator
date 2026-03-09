#pragma once


#include<map>
#include<memory>


enum OperationType {
    Plus,
    Minus,
    Mul,
    Div, 
    LParen,
    RParen
};

class Operation{
    public:
        virtual float change_value(float left, float right) const = 0;
        virtual ~Operation() = default;
};

class AddOperation: public Operation{
    public:
        float change_value(float left, float right) const override;
};

class SubOperation: public Operation{
    public:
        float change_value(float left, float right) const override;
};


class MulOperation: public Operation{
    public:
        float change_value(float left, float right) const override;
};

class DivOperation: public Operation{
    public:
        float change_value(float left, float right) const override;
};




class Calculator{
    private:
        std::map<OperationType, std::unique_ptr<Operation>> registry;
    
    public:
        Calculator() {};
        template <class T> 
        Calculator& RegisterOperation(OperationType name) noexcept {
            registry.emplace(std::move(name), std::make_unique<T>());
            return *this;
        }
        const std::unique_ptr<Operation>& GetOperationByName(OperationType name) const;
        const std::map<OperationType, std::unique_ptr<Operation>>& GetOperatorsMap() const;
};