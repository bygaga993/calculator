#include<iostream>
#include<vector>
#include <memory>
#include<string>
#include "calc.h"
#include "other_func.h"



int main(){
    Calculator calc;
    calc.RegisterOperation<Mul>("multiply").
        RegisterOperation<Add>("add").
        RegisterOperation<Sub>("sub").
        RegisterOperation<Div>("division");

    std::string operation;
    float param1= 0.0f, param2 = 0.0f;
    std::cin >> operation >> param1 >> param2;

    calc.GetOperationByName(operation)->change_value(param1, param2);
}