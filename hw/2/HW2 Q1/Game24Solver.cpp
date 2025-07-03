#include "Game24Solver.h"
#include <cmath>
#include <algorithm>
#include <iostream>


Game24Solver::Game24Solver(const std::vector<int>& numbers) {
	for (int num : numbers) {
		nums.push_back(static_cast<double>(num));
	}
	std::sort(nums.begin(), nums.end()); //升序排序便于使用next_permutation
}

bool Game24Solver::calculate(double a, double b, int op, double& result) const {
	switch (op) {
	case 0:
		result = a + b;
		return true;
	case 1:
		result = a - b;
		return true;
	case 2:
		result = a * b;
		return true;
	case 3:
		if (fabs(b) < 1e-6) {
			return false; //安全性检测，避免用户输入0导致程序出错
		}
		result = a / b;
		return true;
	default:
		return false;
	}
}

bool Game24Solver::method1(int op1, int op2, int op3, double& finalValue, std::string& expression) {
	double a = nums[0], b = nums[1], c = nums[2], d = nums[3];
	double value1, value2;
	std::string aString = std::to_string(static_cast<int>(a));
	std::string bString = std::to_string(static_cast<int>(b));
	std::string cString = std::to_string(static_cast<int>(c));
	std::string dString = std::to_string(static_cast<int>(d));

	if (!calculate(a, b, op1, value1)) {
		return false;
	}
	std::string expression1 = "(" + aString + ops[op1] + bString + ")"; 

	if (!calculate(value1, c, op2, value2)) {
		return false;
	}
	std::string expression2 = "(" + expression1 + ops[op2] + cString + ")"; //和前位运算

	if (!calculate(value2, d, op3, finalValue)) {
		return false;
	}
	expression =  expression2 + ops[op3] + dString ; //和前位运算
	return true;
}

bool Game24Solver::method2(int op1, int op2, int op3, double& finalValue, std::string& expression) {
	double a = nums[0], b = nums[1], c = nums[2], d = nums[3];
	double value1, value2;
	std::string aString = std::to_string(static_cast<int>(a));
	std::string bString = std::to_string(static_cast<int>(b));
	std::string cString = std::to_string(static_cast<int>(c));
	std::string dString = std::to_string(static_cast<int>(d));

	if (!calculate(a, b, op1, value1)) {
		return false;
	}
	std::string expression1 = "(" + aString + ops[op1] + bString + ")";

	if (!calculate(value1, c, op2, value2)) {
		return false;
	}
	std::string expression2 = "(" + expression1 + ops[op2] + cString + ")"; //和前位运算

	if (!calculate(d, value2, op3, finalValue)) {
		return false;
	}
	expression = dString + ops[op3] + expression2; //和后位运算
	return true;
}

bool Game24Solver::method3(int op1, int op2, int op3, double& finalValue, std::string& expression) {
	double a = nums[0], b = nums[1], c = nums[2], d = nums[3];
	double value1, value2;
	std::string aString = std::to_string(static_cast<int>(a));
	std::string bString = std::to_string(static_cast<int>(b));
	std::string cString = std::to_string(static_cast<int>(c));
	std::string dString = std::to_string(static_cast<int>(d));

	if (!calculate(a, b, op1, value1)) {
		return false;
	}
	std::string expression1 = "(" + aString + ops[op1] + bString + ")";

	if (!calculate(c, value1, op2, value2)) {
		return false;
	}
	std::string expression2 = "(" + cString + ops[op2] + expression1 + ")"; //和后位运算

	if (!calculate(value2, d, op3, finalValue)) {
		return false;
	}
	expression = expression2 + ops[op3] + dString; //和前位运算
	return true;
}

bool Game24Solver::method4(int op1, int op2, int op3, double& finalValue, std::string& expression) {
	double a = nums[0], b = nums[1], c = nums[2], d = nums[3];
	double value1, value2;
	std::string aString = std::to_string(static_cast<int>(a));
	std::string bString = std::to_string(static_cast<int>(b));
	std::string cString = std::to_string(static_cast<int>(c));
	std::string dString = std::to_string(static_cast<int>(d));

	if (!calculate(a, b, op1, value1)) {
		return false;
	}
	std::string expression1 = "(" + aString + ops[op1] + bString + ")";

	if (!calculate(c, value1, op2, value2)) {
		return false;
	}
	std::string expression2 = "(" + cString + ops[op2] + expression1 + ")"; //和后位运算

	if (!calculate(d, value2, op3, finalValue)) {
		return false;
	}
	expression = dString + ops[op3] + expression2; //和后位运算
	return true;
}

bool Game24Solver::method5(int op1, int op2, int op3, double& finalValue, std::string& expression) {
	double a = nums[0], b = nums[1], c = nums[2], d = nums[3];
	double value1, value2;
	std::string aString = std::to_string(static_cast<int>(a));
	std::string bString = std::to_string(static_cast<int>(b));
	std::string cString = std::to_string(static_cast<int>(c));
	std::string dString = std::to_string(static_cast<int>(d));

	if (!calculate(a, b, op1, value1)) {
		return false;
	}
	std::string expression1 = "(" + aString + ops[op1] + bString + ")";

	if (!calculate(d, c, op2, value2)) {
		return false;
	}
	std::string expression2 = "(" + dString + ops[op2] + cString + ")"; //先求两和

	if (!calculate(value2, value1, op3, finalValue)) {
		return false;
	}
	expression = expression2 + ops[op3] + expression1; //和运算
	return true;
}

void Game24Solver::solve() {
	do {
		for (int op1 = 0;op1 < 4;++op1) {
			for (int op2 = 0;op2 < 4;++op2) {
				for (int op3 = 0;op3 < 4;++op3) {
					double value;
					std::string expression;
					const double TARGET = 24.0;
					const double EPSILON = 1e-6;

					if (method1(op1, op2, op3, value, expression) && std::fabs(value - TARGET) < EPSILON) {
						solutions.insert(expression);
					}
					if (method2(op1, op2, op3, value, expression) && std::fabs(value - TARGET) < EPSILON) {
						solutions.insert(expression);
					}
					if (method3(op1, op2, op3, value, expression) && std::fabs(value - TARGET) < EPSILON) {
						solutions.insert(expression);
					}
					if (method4(op1, op2, op3, value, expression) && std::fabs(value - TARGET) < EPSILON) {
						solutions.insert(expression);
					}
					if (method5(op1, op2, op3, value, expression) && std::fabs(value - TARGET) < EPSILON) {
						solutions.insert(expression);
					}
				}
			}
		}
	} while (std::next_permutation(nums.begin(), nums.end())); //运用全排列函数
}

void Game24Solver::printSolutions() const {
	if (solutions.empty()) {
		std::cout << "no" << std::endl;
	}
	else {
		for (const auto& expression : solutions) {
			std::cout << expression << std::endl;
		}
	}
}

Game24Solver::~Game24Solver() {
}
