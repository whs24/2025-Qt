#pragma once
#include <vector>
#include <string>
#include <algorithm>


// 大数加法
std::vector<int> add(const std::vector<int>& a, const std::vector<int>& b);

// 大数乘法
std::vector<int> multiply(const std::vector<int>& a, int b);

// 比较两个大数大小
bool compare(const std::vector<int>& a, const std::vector<int>& b);

// 检查两个大数是否相等
bool equals(const std::vector<int>& a, const std::vector<int>& b);

// 将大数转换为字符串
std::string to_string(const std::vector<int>& num);

// 将输入的数字字符串转换为大数形式（逆序存储，低位在前）
std::vector<int> stringToBigInt(const std::string& str);