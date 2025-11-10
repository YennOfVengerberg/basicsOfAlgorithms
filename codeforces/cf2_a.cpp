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
        int temp = 0;
        int result = 0;
        for(int i = 0; i < size; i++) {
            for(int j = i+1; j < size; j++) {
                vector<int> vec_copy = vec;
                vector<int> vec_copy2 = vec;
                vec_copy.erase(vec.begin()+i, vec.begin() + j);
                vec_copy2.erase(vec.begin() + j+1, vec.end());
                temp = maxim(vec_copy2) - minim(vec_copy2);
                result = maxim(vec_copy) - minim(vec_copy); 
                //temp = *max_element(vec.begin()+i, vec.begin() + j) - *min_element(vec.begin()+i, vec.begin() + j);
                //result = max(max(result, temp), maxim(vec_copy) - minim(vec_copy)) ;
            }
        }
        cout << endl << result + temp ;
    }
}