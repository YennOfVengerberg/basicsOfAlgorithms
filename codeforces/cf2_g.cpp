#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    int iter = 0;
    int one = 0, two = 0, res = 0;
    for(int i = 0; i < arr.size();i++) {
        if (arr[i] == 1) {
            one++;
            if(arr[i] != arr[i-1]) {
                res = min(one, two);
            }
        }
        else if (arr[i] == 2) {
            two++;
            if(arr[i] != arr[i-1]) {
                res = min(one, two);
            }
        }

    }
    /*
    vector<int> result;
    
    for(int k = 0; k < result.size(); ++k) {
        cout << result[k] << " ";
    } */

    cout << res;
}