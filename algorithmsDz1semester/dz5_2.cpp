#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;
mt19937 mt(time(nullptr));

int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[right];   
    int i = left - 1;     
    for(int j = left; j <= right-1; j++) { 
        if(arr[j] <= pivot) {           
            i++;                   
            swap(arr[i], arr[j]);   
        }
    }
    swap(arr[i+1], arr[right]);      
    return i + 1;                  
}

int random_partition(vector<int>& arr, int left, int right) {
    uniform_int_distribution<int> distribution(left, right);
    int i = distribution(mt); 
    swap(arr[i], arr[right]); 
    return partition(arr, left, right); 
}

int quick_select(vector<int>& arr, int left, int right, int k) {
    while(true){
        if(left == right) {
            return arr[left];
        } 
        
        int pivot_index = random_partition(arr, left, right);
        
        if(k == pivot_index){       
            return arr[k];
        } else if(k < pivot_index){ 
            right = pivot_index-1;
        } else {              
            left = pivot_index+1;
        }
    }
}

int main() {
    
    int k;
    cout << "введите к " << endl;
    cin >> k;
    vector<int> arr(100);
    for(int i = 0; i < arr.size(); i++ ) {
        arr[i] = mt() % 250;
    }
    //vector<int> arr = {8, 4, 7, 1, 3, 5};
    vector<int> arr_copy = arr;
    sort(arr_copy.begin(), arr_copy.end());
    cout << "sort к-ый " << arr_copy[k-1] << endl; 
    /*for(int i = 0; i < 100; i++) {
        cout << "K-й элемент (" << k << ") : " << quick_select(arr, 0, arr.size()-1, k-1) << endl;
    } */
   cout << "K-й элемент (" << k << ") : " << quick_select(arr, 0, arr.size()-1, k-1) << endl;
}
