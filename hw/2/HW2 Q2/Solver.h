#pragma once
#include "BigInt.h"
#include "Expression.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Solver {
private:
    std::vector<std::vector<int>> numbers;
    int n;
    std::vector<int> target;

public:
    Solver(const std::vector<std::vector<int>>& nums, const std::vector<int>& d);
    void solve();

private:
    void handleSingleNumberCase(); //����һ�������������

    void processResults(const std::vector<Expression>& expressions);
};
