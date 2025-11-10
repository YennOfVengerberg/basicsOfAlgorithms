#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int fun(vector<int> &frequencies) {
    for(int i = 0; i < frequencies.size(); i++) {
        if (frequencies[i] >= 3) {
            return i;
        }
    }
    return -1;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> vec(n);
        for(int i = 0; i < n; i++) {
            cin >> vec[i];
        }
        vector<int> frequencies(*max_element(vec.begin(), vec.end()) + 1, 0);
        for(auto &iter : vec) {
            frequencies[iter]++;
        }
        cout << fun(frequencies) << endl;
    }
}