#include "tokenizer.h"
#include<memory>
#include<string>


float NumberExpr::getNumber() const{
    return value;
};

OperationType OperatorExpr::getType() const{ 
    return type;
}

std::vector<std::unique_ptr<Expr>> Parser::parse(std::string expression){
    for (char c : expression){
        if (std::isdigit(c)){
            float val = c - '0';
            tokens.push_back(std::make_unique<NumberExpr>(c));
        } else if (c == '+'){
            tokens.push_back(std::make_unique<OperatorExpr>(Plus));
        } else if (c == '-'){
            tokens.push_back(std::make_unique<OperatorExpr>(Minus));
        } else if (c == '*'){
            tokens.push_back(std::make_unique<OperatorExpr>(Mul));
        } else if (c == '/'){
            tokens.push_back(std::make_unique<OperatorExpr>(Div));
        } else if (c == '('){
            tokens.push_back(std::make_unique<OperatorExpr>(LParen));
        } else if (c == '('){
            tokens.push_back(std::make_unique<OperatorExpr>(RParen));
    }
    return tokens;
}