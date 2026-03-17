#pragma once

#include <vector>
#include <map>
#include "calc.h"
#include "Operations.h"

class ExpressionParser
{
private:
    std::vector<std::unique_ptr<Expression>> tokens;
    std::vector<std::unique_ptr<Operation>> OpTokens;
    std::vector<std::unique_ptr<Number>> NumTokens;
    const std::map<std::string, std::unique_ptr<Operation>> &operators_;
    void ToPostfix();

public:
    ExpressionParser(const Calculator &calc) : operators_(calc.GetOperatorsMap()) {};
    void Parse(std::string);
    bool ContainsOperation(std::string) const;
    std::vector<std::unique_ptr<Operation>> getOpTokens();
    std::vector<std::unique_ptr<Number>> getNumTokens();
};