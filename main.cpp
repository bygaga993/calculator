#include<iostream>
#include<vector>
#include <memory>
#include<string>
#include "calc.h"
#include "other_func.h"



int main(){
    Calculator calc;
    calc.RegisterOperation<Add>("+").
        RegisterOperation<Sub>("-");
    
    std::cout << parse_expression(calc);
}