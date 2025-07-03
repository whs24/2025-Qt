#pragma once
#include <vector>
#include <string>
#include <algorithm>


// �����ӷ�
std::vector<int> add(const std::vector<int>& a, const std::vector<int>& b);

// �����˷�
std::vector<int> multiply(const std::vector<int>& a, int b);

// �Ƚ�����������С
bool compare(const std::vector<int>& a, const std::vector<int>& b);

// ������������Ƿ����
bool equals(const std::vector<int>& a, const std::vector<int>& b);

// ������ת��Ϊ�ַ���
std::string to_string(const std::vector<int>& num);

// ������������ַ���ת��Ϊ������ʽ������洢����λ��ǰ��
std::vector<int> stringToBigInt(const std::string& str);