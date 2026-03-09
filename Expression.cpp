#include "Expression.h"
#include<memory>
#include<string>
#include<iostream>


float NumberExpr::getNumber() const{
    return value;
};

OperationType OperatorExpr::getType() const{ 
    return type;
}

void NumberExpr::Print() const {
    std::cout << value;
}

void OperatorExpr::Print() const {
    switch (type){
        case Plus: std::cout << '+'; break;
        case Minus: std::cout << '-'; break;
        case Mul: std::cout << '*'; break;
        case Div: std::cout << '/'; break;
        case LParen: std::cout << '('; break;
        case RParen: std::cout << ')'; break;
    }
}

bool NumberExpr::IsNumber() const{
    return true;
}

bool OperatorExpr::IsNumber() const{
    return false;
}

float NumberExpr::AsNumber() const{
    return value;
}

float OperatorExpr::AsNumber() const{
    throw std::runtime_error("it is Operation Expr");
}


float OperatorExpr::change_value(float left, float right){
    return op->change_value(left, right);
}
