#include <iostream>
#include <vector>
#include <random>

using namespace std;
mt19937 mt(time(nullptr));
const unsigned int S = 16;

void pairs(vector<pair<int, int>> &vec, int left, int right) {
    int i = left, j = right;
    while(i < j) {
        if (vec[i].first + vec[j].first == S ) {
            cout << vec[i].second << " " << vec[j].second << " | ";
            i++;
        } else if (vec[i].first + vec[j].first < S) {
            i++;
        } else {
            j--;
        }
    }
    
}

void merger(vector<pair<int,int>> &vec, int left, int mid, int right) {
    vector<pair<int,int>> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    
    while(i <= mid && j <= right) {
        if(vec[i] <= vec[j]) {
            if(vec[i].first + vec[j].first == S) {
                cout << vec[i].second << " " << vec[j].second << " | ";
            }
            temp[k++] = vec[i++];
        } else {
            if(vec[i].first + vec[j].first == S) {
                cout << vec[i].second << " " << vec[j].second << " | ";
            }
            temp[k++] = vec[j++];
        }
    }
    
    while(i <= mid) {
        temp[k++] = vec[i++];
    }
    pairs(temp, 0, k-1);
    while(j <= right) {
        temp[k++] = vec[j++];
    }
    pairs(temp, mid, k-1);

    for(int p = left; p <= right; p++) {
        vec[p] = temp[p-left];
    }
    

    
}



void merge_fun(vector<pair<int,int>> &vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left)/2;
        
        merge_fun(vec, left, mid);

        merge_fun(vec, mid + 1, right);
        
        merger(vec, left, mid, right);
    }
}

void checker_sq(vector<pair<int,int>> &vec, unsigned int S ) {
    for(int i = 0; i < vec.size(); i++) {
        for(int j = i + 1; j < vec.size(); j++) {
            if(vec[i].first + vec[j].first == S ) {
                cout << vec[i].second << " " << vec[j].second << endl;
            }
        }
    }
}



int main() {
    
    
    cout << " inp vec size " << endl;
    int size;
    cin >> size; 
    vector<pair<int,int>> vec(size);
    //vector<pair<int,int>> vec = { {3, 1}, {0, 2}, {12, 3}, {6,4}, {11,5}, {16,6}, {5,7},  {22,8},  };
    for(int i = 0; i < size; i++) {
        vec[i] = {mt() % 100, i};
    }
    checker_sq(vec, S);
    merge_fun(vec, 0, vec.size() - 1);

    /*for(int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }*/
}