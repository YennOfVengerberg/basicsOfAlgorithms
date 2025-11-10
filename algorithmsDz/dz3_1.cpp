#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <algorithm>

using namespace std;

void merge(vector<int> &vec, int left, int mid, int right) {
    int size1 = mid - left + 1;
    int size2 = right - mid;

    vector<int> leftVec(size1);
    vector<int> rightVec(size2);
    
    for (int i = 0; i < size1; i++) leftVec[i] = vec[left + i];
    for (int j = 0; j < size2; j++) rightVec[j] = vec[mid + 1 + j];
    int i = 0, j = 0, k = left;

    while (i < size1 && j < size2) {
        if (leftVec[i] <= rightVec[j]) {
            vec[k] = leftVec[i];
            i++;
        } else {
            vec[k] = rightVec[j];
            j++;
        }
        k++;
    }
    
}

void insertionSort(vector<int> &vec) {
    int n = vec.size();
    for (int i = 1; i < n; i++) {
        int key = vec[i];
        int j = i - 1;
        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = key;
    }
}

void modifiedMergeSort(vector<int> &vec, int left, int right, int threshold)
{
    if (right - left + 1 <= threshold) insertionSort(vec);
    else {
        if (left < right) {
            int mid = left + (right - left) / 2;
            modifiedMergeSort(vec, left, mid, threshold);
            modifiedMergeSort(vec, mid + 1, right, threshold);
            merge(vec, left, mid, right);
        }
    } 
}

int main()
{
    int n;
    double threshold = 0;
    mt19937 mt(time(0));
    
    for(int n = 1000; n < pow(10,7); n *= 10) {
        vector<int> vec;
        for(int i = 0; i < n; i++) {
            vec.push_back(mt() % 10000); // лимит 10000 для примера, 10^7
            //cout << vec[i] << " ";
        }
        chrono::duration<double> before = 24h;
        for(int i = 1; i < 1000; i++) { // i < 1000; for n up to 10^6; sort = modifiedsort
            auto start = chrono::steady_clock::now();
            vector<int> vec_copy = vec;
            modifiedMergeSort(vec_copy, 0, n - 1, i);
            auto end = chrono::steady_clock::now();
            chrono::duration<double> elapsed = end - start;
            sort(vec.begin(), vec.end());
            if (elapsed < before && vec_copy == vec) {
                before = elapsed;
                threshold = i;
                cout << before.count() << " "<< threshold << endl;
            }
            else if (vec_copy != vec) {
                cerr << "Ошибка сортировки!" << endl;
                break;
            }
        }
    }
    
    //cout << endl << "Отсортированный массив: "; 
    //for (int i = 0; i < n; i++) cout << vec[i] << " ";
    cout << endl << " граница " << threshold;
    // 1000 - 18-31, 10000 - 38-93, 100'000+ ~ sqrt(n)
    // в среднем граница перехода(m) стремится к sqrt(n)
}