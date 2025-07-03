#pragma once

#include <vector>
#include <set>
#include <string>

class Game24Solver {
public:
    Game24Solver(const std::vector<int>& numbers);
    ~Game24Solver();
    void solve();
    void printSolutions() const;

private:
    std::vector<double> nums;
    std::set<std::string> solutions; //set保证不重复
    const char ops[4] = { '+', '-', '*', '/' };

    bool calculate(double a, double b, int op, double& result) const; //进行一步运算，代表括号复合
    bool method1(int op1, int op2, int op3, double& finalVal, std::string& expr);
    bool method2(int op1, int op2, int op3, double& finalVal, std::string& expr);
    bool method3(int op1, int op2, int op3, double& finalVal, std::string& expr);
    bool method4(int op1, int op2, int op3, double& finalVal, std::string& expr); //五种不同的模式代表着不同的运算顺序
    bool method5(int op1, int op2, int op3, double& finalVal, std::string& expr); //不考虑各自是第几个数字，仅考虑运算顺序
};
