#pragma once
#include "BigInt.h"
#include <vector>
#include <string>
#include <algorithm>

class Expression {
private:
    std::vector<std::vector<int>> numbers;
    std::vector<char> operators;
    std::vector<int> result;
    std::string exprStr;

public:
    Expression(const std::vector<std::vector<int>>& nums);
    void setOperators(const std::vector<char>& ops);  //������������������ͱ��ʽ
    std::vector<int> getResult() const;
    std::string getExpressionString() const;

private:
    void calculateResult();
    void buildExpressionString();
};


