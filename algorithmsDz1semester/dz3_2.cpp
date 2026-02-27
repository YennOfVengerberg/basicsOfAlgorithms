#include <iostream>
#include <vector>
#include <random>
using namespace std;

// Функция вычисляет количество интересующих пар и одновременно сортирует массив
int merge_and_count(vector<int> &arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1); // Временный буфер для объединения
    
    int i = left, j = mid + 1, k = 0;
    int count = 0;
    
    while(i <= mid && j <= right) {
        if(arr[i] <= arr[j]) { // Элементы расположены правильно
            temp[k++] = arr[i++];
        } else { // Здесь возникает интересная пара (i < j, a[i] > a[j])
            temp[k++] = arr[j++];
            count += (mid - i + 1); // Все элементы слева больше текущего элемента справа
        }
    }
    
    // Добавляем оставшиеся элементы
    while(i <= mid)
        temp[k++] = arr[i++];
        
    while(j <= right)
        temp[k++] = arr[j++];
    
    // Временный массив назад в оригинальный
    for(int p = left; p <= right; ++p)
        arr[p] = temp[p-left];
    
    return count;
}

// Разделение массива и подсчета пар
int count_pairs(vector<int> &arr, int left, int right) {
    if(left >= right)
        return 0;
    
    int mid = left + (right - left)/2;
    
    // Подсчет пар внутри двух половинок
    int x = count_pairs(arr, left, mid);
    int y = count_pairs(arr, mid+1, right);
    
    // Объединение и подсчет перекрестных 
    int z = merge_and_count(arr, left, mid, right);
    
    return x+y+z;
}

int checker(vector<int> &vec) {
    int check = 0;
    for(int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < vec.size(); j++) {
            if(i < j && vec[i] > vec[j]) {
                check++;
            }
        }
    }
    return check;
}

int main() {
    int n;
    cout << "Размер " << endl;
    cin >> n;
    vector<int> arr(n); // = {1, 325, 654, 23, 748, 123, 67, 164, 120} ; //0 + 5 + 5 + 0 + 4 +2 + 1 = 17 
    
    mt19937 mt(time(nullptr));
    for(int i = 0; i < n; i++)
        arr[i] = mt();  
    cout << "Количество интересных пар: " << checker(arr) << " " << count_pairs(arr, 0, arr.size()-1) << endl;
}
