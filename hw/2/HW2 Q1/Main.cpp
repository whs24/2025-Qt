#include "Game24Solver.h"
#include <iostream>
#include <vector>

int main() {
    std::cout << "�������ĸ�Ҫ����24������֣��ÿո����):\n";
    std::vector<int> numbers; //�û��ṩ������
    for (int i = 0; i < 4; i++) { //�ɸı����������п���չ��
        int num;
        std::cin >> num;
        numbers.push_back(num);
    }

    Game24Solver solver(numbers);
    solver.solve();
    solver.printSolutions();

    return 0;
}