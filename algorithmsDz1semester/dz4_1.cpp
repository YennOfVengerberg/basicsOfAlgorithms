#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
mt19937 mt(time(nullptr));

void heapify(vector<int>& arr, int n, int i){
    int largest = i;

    int l = 3 * i + 1;
    int mid =  3 * i + 2;
    int r = 3 * i + 3;

    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }
        
    if(mid < n && arr[mid] > arr[largest]) {
        largest = mid;
    }
        
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }
        
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = (n-2)/3; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    for(int size = 1000; size <= pow(10, 8); size *= 10) {
        vector<int> arr(size);
        for(int i = 0; i < size; i++) {
            arr[i] = mt() % 1000;
        }
        vector<int> vec_copy = arr;

        sort(vec_copy.begin(), vec_copy.end());

        heap_sort(arr);

        
        /* for (int i = 0; i < arr.size(); ++i)
            cout << arr[i] << " "; */
        if (vec_copy == arr) {
            cout << "верно " << endl;
        } else {
            cerr << "неверно " << endl;
        } 
    }
    
}   