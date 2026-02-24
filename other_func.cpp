#include <string>
#include "calc.h"
#include<iostream>


void lower(std::string& str){
    for (char &c: str){
        c = std::tolower(c);
    }
}

float parse_expression(Calculator& calc){
    float result;

    std::cin >> result;
    while (true) {
        std::string op;
        std::cin >> op;

        if (op == "="){
            break;
        } 
        float value;
        std::cin >> value;

        result = calc.GetOperationByName(op)->change_value(result, value);
    }

}