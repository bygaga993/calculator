#pragma once

#include<vector>
#include "tokenizer.h"

class ExpressionParser {
    private:
        std::vector<std::unique_ptr<Expr>> tokens;
    public:
        ExpressionParser(std::vector<std::unique_ptr<Expr>> t) : tokens(std::move(t)) {};
        void ToPostfix();  
        void Print() const;
        std::vector<std::unique_ptr<Expr>> getTokens();
};