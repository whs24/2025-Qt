#include "Game24Solver.h"
#include <iostream>
#include <vector>

int main() {
    std::cout << "请输入四个要计算24点的数字（用空格隔开):\n";
    std::vector<int> numbers; //用户提供的数字
    for (int i = 0; i < 4; i++) { //可改变条件，具有可扩展性
        int num;
        std::cin >> num;
        numbers.push_back(num);
    }

    Game24Solver solver(numbers);
    solver.solve();
    solver.printSolutions();

    return 0;
}