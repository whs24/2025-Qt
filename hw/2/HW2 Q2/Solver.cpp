#include "Solver.h"


Solver::Solver(const std::vector<std::vector<int>>& nums, const std::vector<int>& d)
        : numbers(nums), n(nums.size()), target(d) {}

void Solver::solve() {
        if (n == 1) {
            handleSingleNumberCase();
            return;
        }

        std::vector<Expression> expressions;
        int opCount = n - 1;
        int totalCombinations = 1 << opCount;  //���Ƽ���2^n-1���������ŵ������

        for (int i = 0; i < totalCombinations; i++) {
            std::vector<char> ops(opCount);
            for (int j = 0; j < opCount; j++) {
                ops[j] = (i & (1 << j)) ? '*' : '+';  //����������еĿ��ܣ����ƹ�����jȡ��1��ѭ��������iȡ�����ж���������
            }

            Expression expr(numbers);
            expr.setOperators(ops);
            expressions.push_back(expr);
        }

        processResults(expressions);
    }


    void Solver::handleSingleNumberCase() {
        if (equals(numbers[0], target)) {
            std::cout << to_string(numbers[0]) << std::endl;
        }
        else {
            std::cout << "No" << std::endl;
            if (compare(numbers[0], target)) {
                std::cout << to_string(numbers[0]) << std::endl;
            }
            else {
                std::cout << "-1" << std::endl;
            }
        }
    }

    void Solver::processResults(const std::vector<Expression>& expressions) {
        bool found = false;
        std::string exprStr;  //��ĿҪ�����һ����Ӧ���ʽ����
        std::vector<int> minGreater;
        bool hasMinGreater = false;

        for (const auto& expr : expressions) {
            if (equals(expr.getResult(), target)) {
                found = true;
                exprStr = expr.getExpressionString();
                break;  
            }
            if (compare(expr.getResult(), target)) {
                if (!hasMinGreater || compare(minGreater, expr.getResult())) {
                    minGreater = expr.getResult();
                    hasMinGreater = true;
                }
            }
        }

        if (found) {
            std::cout << exprStr << std::endl;
        }
        else {
            std::cout << "No" << std::endl;
            if (hasMinGreater) {
                std::cout << to_string(minGreater) << std::endl;
            }
            else {
                std::cout << "-1" << std::endl;
            }
        }
    }
