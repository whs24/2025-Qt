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
    std::set<std::string> solutions; //set��֤���ظ�
    const char ops[4] = { '+', '-', '*', '/' };

    bool calculate(double a, double b, int op, double& result) const; //����һ�����㣬�������Ÿ���
    bool method1(int op1, int op2, int op3, double& finalVal, std::string& expr);
    bool method2(int op1, int op2, int op3, double& finalVal, std::string& expr);
    bool method3(int op1, int op2, int op3, double& finalVal, std::string& expr);
    bool method4(int op1, int op2, int op3, double& finalVal, std::string& expr); //���ֲ�ͬ��ģʽ�����Ų�ͬ������˳��
    bool method5(int op1, int op2, int op3, double& finalVal, std::string& expr); //�����Ǹ����ǵڼ������֣�����������˳��
};
