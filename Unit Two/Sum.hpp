#ifndef SUM_HPP
#define SUM_HPP

#include <vector>

using namespace std;


int sum(const vector<int>& vec) {
    int total = 0;
    for (int num : vec) {
        total += num;
    }
    return total;
}

#endif