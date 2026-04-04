#pragma once

#include <vector>
#include <map>
#include "calc.h"
#include "Operations.h"



class ExpressionParser
{
private:
    std::vector<std::shared_ptr<Expression>> tokens;
    std::vector<std::shared_ptr<Operation>> OpTokens;
    std::vector<std::shared_ptr<Number>> NumTokens;
    std::vector<std::shared_ptr<Expression>> OrderTokens;
    const std::map<std::string, std::unique_ptr<Operation>> &operators_;
    void ToPostfix();

    void SkipSpaces(const std::string&, size_t& );
    float ParseNumber(const std::string&, size_t&, bool);

public:
    ExpressionParser(const Calculator &calc) : operators_(calc.GetOperatorsMap()) {};
    void Parse(std::string);
    bool ContainsOperation(std::string) const;
    std::vector<std::shared_ptr<Operation>> getOpTokens();
    std::vector<std::shared_ptr<Number>> getNumTokens();
    std::vector<std::shared_ptr<Expression>> getOrderTokens();
};