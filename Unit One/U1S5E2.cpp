#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> vec1 = {6, 3, 5, 2, 4};
    vector<int> vec2 = {1, 4, 8, 4, 3};
    
    vector<int> merged = vec1;
    merged.insert(merged.end(), vec2.begin(), vec2.end());
    
    sort(merged.begin(), merged.end());
    
    cout << "Merged and sorted vector: ";
    for (int num : merged) {
        cout << num << " ";
    }
    cout << endl;
}