#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minim(vector<int> vec) {
    int minim = 10000000;
    for(int i = 0; i < vec.size(); i++) {
        minim = min(minim, vec[i]);
    }
    return minim;
}

int maxim(vector<int> vec) {
    int maxim = 0;
    for(int i = 0; i < vec.size(); i++) {
        maxim = max(maxim, vec[i]);
    }
    return maxim;
}

int main() {
    int n;
    cin >> n;
    while (n--) {
        int size = 0;
        cin >> size;
        vector<int> vec(size);
        for(int i = 0; i < size; i++) {
            cin >> vec[i];
        }
        int otr = 0;
        int result = 0;
        int maxim = 0;
        int minim = 10000000;
        for(int i = 0; i < size; i++) {
            for(int j = i+1; j < size; j++) {
                maxim = max(*max_element(vec.begin(), vec.begin() + i), *max_element(vec.begin()+j, vec.end()));
                minim = min(*min_element(vec.begin(), vec.begin() + i), *min_element(vec.begin()+j, vec.end()));
                otr = *max_element(vec.begin()+i, vec.begin() + j) - *min_element(vec.begin()+i, vec.begin() + j);
                //result = max(max(result, temp), maxim(vec_copy) - minim(vec_copy)) ;
            }
        }
        cout << endl << result + otr;
    }
}
/* 
4
8
1 2 2 3 1 5 6 1
5
1 2 3 100 200
4
3 3 3 3
6
7 8 3 1 1 8
*/