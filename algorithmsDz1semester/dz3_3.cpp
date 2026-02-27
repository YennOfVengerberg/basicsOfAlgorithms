#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;
mt19937 mt(time(nullptr));
const unsigned int S = mt() % 1000;
vector<pair<int,int>> results;

vector<pair<int, int>> generation(int size) {
    mt19937 mt(time(nullptr));
    int i = 0, el = 0;
    vector<pair<int, int>> generated(size);
    vector<int> pre_res(size);
    while(i < size) {
        el = (mt() % 1000);
        if (find(pre_res.begin(), pre_res.end(), el) == pre_res.end()) {
            pre_res[i] = el; 
            i++;
        }  
    }
    for(int i = 0; i < size; i++ ) {
        generated[i] = {pre_res[i], i};
    }    
    return generated;
}

void pairs(vector<pair<int, int>> &vec, int left, int mid, int right, vector<pair<int,int>> &results) {
    int i = left, j = right;
    while(i <= mid && mid+1 <= j) {
        if (vec[i].first + vec[j].first == S ) {
            results.push_back({vec[i].second, vec[j].second});
            //cout << vec[i].second << " " << vec[j].second << " | ";
            i++;
            j--;
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
    pairs(vec, left, mid, right, results);
    
    while(i <= mid && j <= right) {
        if(vec[i] <= vec[j]) {
            temp[k++] = vec[i++];
        } else {
            temp[k++] = vec[j++];
        }
    }
    
    while(i <= mid) {
        temp[k++] = vec[i++];
    }
    while(j <= right) {
        temp[k++] = vec[j++];
    }

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
                cout << vec[i].second << " " << vec[j].second << " | ";
            }
        }
    }
}

int main() {
    cout << " inp vec size " << endl;
    int size;
    cin >> size; 
    vector<pair<int,int>> vec;
    cout << " S = " << S << endl;
    //vector<pair<int,int>> vec = { {3, 1}, {0, 2}, {12, 3}, {6,4}, {11,5}, {16,6}, {5,7},  {22,8},  };
    vec = generation(size);
    checker_sq(vec, S);
    cout << endl << endl;
    merge_fun(vec, 0, vec.size() - 1);

    sort(results.begin(), results.end());

    if(results.empty()) {
        cout << "нет пар " << endl;
    } else {
        for(int i = 0; i < results.size(); i++ ) {
            cout << results[i].first << " " << results[i].second << " | ";
        }
    }

    /*for(int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }*/
}