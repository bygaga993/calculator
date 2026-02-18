#include "calc.h"
#include<cmath>

float Add::change_value(float& res_value) const{
    return number + res_value;
}

float Sub::change_value(float& res_value) const{
    return res_value - number;
}

float Mul::change_value(float& res_value) const{
    return res_value * number;
}

float Div::change_value(float& res_value) const{
    return res_value / number;
}

float Pow::change_value(float& res_value) const{
    return pow(res_value, number);
}

float SquareRoot::change_value(float& res_value) const{
    return sqrt(res_value);
}

float Square::change_value(float& res_value) const{
    return pow(res_value, 2);
}


void Calculator::add_operation(std::unique_ptr<Operation> op){
    operations.push_back(std::move(op));
}

float Calculator::return_result(){
    for (auto& ptr: operations){
        start_value = ptr->change_value(start_value);
    }
    return start_value;
}