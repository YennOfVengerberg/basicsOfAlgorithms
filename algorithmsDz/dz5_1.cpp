#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
mt19937 mt(time(nullptr));

void qsort(vector<int>& arr, int begin, int end) {
    if (begin >= end) return;

    int randomIndex = begin + mt() % (end-begin+1);
    swap(arr[begin], arr[randomIndex]);
    int pivot = arr[begin];

    int less = begin + 1;
    int greater = end;       
    int curr = begin + 1;        

    while (curr <= greater) {
        if (arr[curr] < pivot) {  
            swap(arr[curr++], arr[less++]);  
        }
        else if (arr[curr] > pivot) {      
            swap(arr[curr], arr[greater--]);    
        } else {                          
            curr++;                        
        }
    }

    qsort(arr, begin, less - 1); 
    qsort(arr, greater + 1, end);   
}

int main() {
    /*cout << "size " << endl;
    int size;
    cin >> size;
    vector<int> vec(size); */

    for(int i = pow(10,7); i <= pow(10,8); i *= 10) {
        vector<int> vec(i);
        for(int j = 0; j < vec.size(); j++) {
            vec[j] = mt() % 100;
        }

        vector<int> vec_copy = vec;

        auto start = chrono::steady_clock::now();
        sort(vec_copy.begin(), vec_copy.end());
        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsed = end - start;

        start = chrono::steady_clock::now();
        qsort(vec, 0, vec.size()-1);
        end = chrono::steady_clock::now();
        chrono::duration<double> elapsed2 = end - start;
        if(vec == vec_copy) {
            cout << "sorted right for size " << i << " std sort time " << elapsed.count() << " my sort time " << elapsed2.count() << endl;
        } else {
            cerr << "err " << endl;
        }
    }
    
}