#pragma once

#include<vector>
#include<map>
#include "calc.h"
#include "Operations.h"


class ExpressionParser {
    private:
        std::vector<std::unique_ptr<Expression>> tokens;
        const std::map<std::string, std::unique_ptr<Operation>>& operators_;
    public:
        ExpressionParser(const Calculator& calc) : operators_(calc.GetOperatorsMap()){};
        void Parse(std::string);
        void ToPostfix();  
        void Print() const;
        bool ContainsOperation(std::string) const;
        std::vector<std::unique_ptr<Expression>> getTokens();
};