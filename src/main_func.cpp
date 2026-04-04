#include "../include/main_func.h"
#include "../include/Operations.h"

float getResult(std::vector<std::shared_ptr<Operation>>& OpTokens, std::vector<std::shared_ptr<Number>>& NumTokens, 
    std::vector<std::shared_ptr<Expression>>& OrderTokens){
        std::stack<float> resultStack;

    size_t numberIndex = 0;
    size_t opIndex = 0;

    for (auto& el: OrderTokens){
        if (el->isNumber()){
            resultStack.push(NumTokens[numberIndex]->getValue());
            numberIndex++;
        } else {
            if (resultStack.size() < 2)
            {
                throw std::runtime_error("Not enough operands for operation");
            }

            float right = resultStack.top();
            resultStack.pop();
            float left = resultStack.top();
            resultStack.pop();

            float result = OpTokens[opIndex]->return_value(left, right);
            resultStack.push(result);
            opIndex++;
        }
    }
    return resultStack.top();
}