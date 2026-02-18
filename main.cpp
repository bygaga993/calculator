#include<iostream>
#include<vector>
#include <memory>
#include<string>
#include "calc.h"
#include "other_func.h"



int main(){
    std::vector<std::unique_ptr<Operation>> opr;
    std::cout << "available operations: add, sub, mul, div, pow \n";
    std::cout << "enter starting value:  ";
    float start;
    std::cin >> start;
    Calculator process(start);
    while (true){
        std::string inserd_operation;
        std::cin >> inserd_operation;

        lower(inserd_operation);

        if (inserd_operation == "equals") {
            std::cout << '\n' << process.return_result();
            break;
        } 
        float inserd_value;
        std::cin >> inserd_value;
        if (inserd_operation == "add"){
            process.add_operation(std::make_unique<Add>(inserd_value));
        } else if (inserd_operation == "sub"){
            process.add_operation(std::make_unique<Sub>(inserd_value));
        } else if (inserd_operation == "mul"){
            process.add_operation(std::make_unique<Mul>(inserd_value));
        } else if (inserd_operation == "div"){
            process.add_operation(std::make_unique<Div>(inserd_value));
        } else if (inserd_operation == "pow"){
            process.add_operation(std::make_unique<Pow>(inserd_value));
        }
    }
    return 0;
}