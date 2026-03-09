#pragma once

#include<vector>
#include<map>
#include "calc.h"
#include "Expression.h"


class ExpressionParser {
    private:
        std::vector<std::unique_ptr<Expr>> tokens;
        const std::map<OperationType, std::unique_ptr<Operation>>& operators_;
    public:
        ExpressionParser(const Calculator& calc) : operators_(calc.GetOperatorsMap()){};
        void Parse(std::string);
        void ToPostfix();  
        void Print() const;
        std::vector<std::unique_ptr<Expr>> getTokens();
        bool ContainsOperation(OperationType) const;
};