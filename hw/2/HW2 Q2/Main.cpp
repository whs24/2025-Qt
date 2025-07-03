#include <iostream>
#include <vector>
#include <string>
#include "Solver.h"

using namespace std;

int main() {
    int N;
    string D;
    cin >> N >> D;

    vector<vector<int>> numbers(N);
    for (int i = 0; i < N; i++) {
        string numStr;
        cin >> numStr;
        numbers[i] = stringToBigInt(numStr);
    }

    vector<int> target = stringToBigInt(D);

    Solver solver(numbers, target);
    solver.solve();

    return 0;
}