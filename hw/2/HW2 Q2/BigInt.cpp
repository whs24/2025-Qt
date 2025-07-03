#include "BigInt.h"

std::vector<int> add(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> c;
    int carry = 0;      //���ڴ����λ��Ϣ                                                                                                                                                                                                 
    for (size_t i = 0; i < std::max(a.size(), b.size()) || carry; i++) {
        if (i < a.size()) carry += a[i];
        if (i < b.size()) carry += b[i];
        c.push_back(carry % 10);
        carry /= 10;
    }
    return c;
}

std::vector<int> multiply(const std::vector<int>& a, int b) {
    std::vector<int> c;
    long long carry = 0;
    for (size_t i = 0; i < a.size() || carry; i++) {
        if (i < a.size()) carry += (long long)a[i] * b;
        c.push_back(carry % 10);
        carry /= 10;
    }
    // �Ƴ�ǰ���㣨ĳ����0��
    while (c.size() > 1 && c.back() == 0) c.pop_back();
    return c;
}

bool compare(const std::vector<int>& a, const std::vector<int>& b) {  //a>b����1
    if (a.size() != b.size()) return a.size() > b.size();
    for (int i = a.size() - 1; i >= 0; i--) {
        if (a[i] != b[i]) return a[i] > b[i];
    }
    return false; // ���
}

bool equals(const std::vector<int>& a, const std::vector<int>& b) {
    return !compare(a, b) && !compare(b, a);
}

std::string to_string(const std::vector<int>& num) {
    if (num.empty()) return "0";
    std::string result;
    for (int i = num.size() - 1; i >= 0; i--) {  // ����洢����λ��ǰ
        result += (char)(num[i] + '0');
    }
    return result;
}

std::vector<int> stringToBigInt(const std::string& str) {
    std::vector<int> num;
    for (char c : str) {
        num.push_back(c - '0');
    }
    reverse(num.begin(), num.end()); // ����洢����λ��ǰ
    return num;
}