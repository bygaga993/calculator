#include "calc.h"
#include "ExpressionParser.h"
#include "Operations.h"


float getResult(std::vector<std::shared_ptr<Operation>> OpTokens, std::vector<std::shared_ptr<Number>> NumTokens, 
    std::vector<std::shared_ptr<Expression>> OrderTokens);