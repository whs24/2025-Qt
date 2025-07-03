#include "Expression.h"

Expression::Expression(const std::vector<std::vector<int>>& nums) : numbers(nums) 
{
}

void Expression::setOperators(const std::vector<char>& ops) {
     operators = ops;
     calculateResult();
     buildExpressionString();
 }

std::vector<int> Expression::getResult() const {
        return result;

    }

std::string Expression::getExpressionString() const {
        return exprStr;
    }

void Expression::calculateResult() {
        result = numbers[0];
        for (size_t i = 0; i < operators.size(); i++) {
            if (operators[i] == '+') {
                result = add(result, numbers[i + 1]);
            }
            else {
                // 假设numbers[i+1]可以转换为int（因为实际题目中表述的数字范围为1-13）
                result = multiply(result, stoi(to_string(numbers[i + 1])));
            }
        }
    }

void Expression::buildExpressionString() {
        exprStr = to_string(numbers[0]);
        for (size_t i = 0; i < operators.size(); i++) {
            exprStr += operators[i] + to_string(numbers[i + 1]);
        }
    }

