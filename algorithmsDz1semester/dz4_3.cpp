#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

using namespace std;
mt19937 mt(time(nullptr));

void counting_sort(vector<long long>& arr, int exp, int N) {
    int n = arr.size();
    vector<long long> output(n);    
    vector<long long> count(N, 0);  

    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % N;
        count[digit]++;
    }

    for (int i = 1; i < N; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % N;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    arr = output;
}

void radixSort(vector<long long>& arr, int n) {
    int max_num = *max_element(arr.begin(), arr.end()); 
    int digits_count = floor(log(max_num)/log(n)) + 1;       // log(n^3) / log(n) = logn (n^3) свойство логарифма

    for (int exp = 1; digits_count-- > 0; exp *= n) {
        counting_sort(arr, exp, n);
    }
}

void generate_array(vector<long long>& arr, int n) {
    
    uniform_int_distribution<> dis(0, pow(n, 3)-1); 
    
    for(int i = 0; i < n; i++) {
        arr.push_back(dis(mt));
    }
}

int main() {
    int N; 
    cout << "size " << endl;
    cin >> N; 
    vector<long long> arr;
    generate_array(arr, N);
    vector<long long> arr_copy = arr;

    radixSort(arr, N);
    sort(arr_copy.begin(), arr_copy.end());
    
    if(arr_copy == arr) {
        cout << "sorted right " << endl;
    } else {
        cerr << "err " << endl;
    }

    return 0;
}
/*
общую асимптотику функции можно оценить как O(k * (n + d)),
где k - количество разрядов в максимальном элементе maxElement, n - размер входного вектора arr, d - алфавит .

Возьмем изначально десятичную СС, то есть d = 10. Тогда количество разрядов в maxelement k = log10(n^3) в худшем случае. 
Но тогда получаем общую сложность O(log10(n^3) * (n+10) )) = O(log10(n^3) * n) != O(n)

Отсюда можно догадаться, что надо взять d = n. Получим k = logn(n^3) = 3*logn(n) = 3 по свойству логарифма. Получим:
O(3*(n+n) ) = O(3*2n) = O(6n) = O(n)
*/

