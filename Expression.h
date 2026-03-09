#pragma once
#include "calc.h"
#include<memory>


class Expr {
    public:
        virtual ~Expr() = default;
        virtual bool IsNumber() const = 0;
        virtual void Print() const = 0;
        virtual float AsNumber() const = 0;
        virtual float change_value(float, float){
            throw std::runtime_error("it is Number Expr");
        };
};

class NumberExpr: public Expr {
    private:
        float value;
    public:
        NumberExpr(float v): value(v) {};
        float getNumber() const;
        bool IsNumber() const;
        void Print() const;
        float AsNumber() const;
};

class OperatorExpr: public Expr {
    private:
        OperationType type; 
        std::unique_ptr<Operation> op = nullptr;
    public:
        bool operator<(const OperatorExpr& other) const {
            return type < other.type;
        }
        
        OperatorExpr(OperationType t): type(t) {
            switch (t) {
            case Plus:
                op = std::make_unique<AddOperation>();
                break;
            case Minus:
                op = std::make_unique<SubOperation>();  
                break;
            case Mul:
                op = std::make_unique<MulOperation>();
                break;
            case Div:
                op = std::make_unique<DivOperation>(); 
                break;
            case LParen: break;
            case RParen: break;
            }
        };
        OperationType getType() const;
        bool IsNumber() const;
        void Print() const;
        float AsNumber() const;
        float change_value(float left, float right);
};