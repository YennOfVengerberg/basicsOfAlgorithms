#include <iostream>
#include <vector>
using namespace std;

// Функция вычисляет количество интересующих пар и одновременно сортирует массив
int merge_and_count(vector<int> &arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1); // Временный буфер для объединения
    
    int i = left, j = mid + 1, k = 0;
    int count = 0;
    
    while(i <= mid && j <= right) {
        if(arr[i] <= arr[j]) { // Элементы расположены правильно
            temp[k++] = arr[i++];
        } else { // Здесь возникает интересная пара
            temp[k++] = arr[j++];
            count += (mid - i + 1); // Все элементы слева больше текущего элемента справа
        }
    }
    
    // Добавляем оставшиеся элементы
    while(i <= mid)
        temp[k++] = arr[i++];
        
    while(j <= right)
        temp[k++] = arr[j++];
    
    // Копируем временный массив назад в оригинальный
    for(int p = left; p <= right; ++p)
        arr[p] = temp[p-left];
    
    return count;
}

// Рекурсивная функция разделения массива и подсчета пар
int count_pairs(vector<int> &arr, int left, int right) {
    if(left >= right)
        return 0;
    
    int mid = left + (right - left)/2;
    
    // Подсчет пар внутри двух половинок
    int x = count_pairs(arr, left, mid);
    int y = count_pairs(arr, mid+1, right);
    
    // Объединение и подсчет перекрестных пар
    int z = merge_and_count(arr, left, mid, right);
    
    return x+y+z;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr; // = {1, 325, 654, 23, 748, 123, 67, 164, 120} ; 0 + 5 + 5 + 0 + 4 +2 + 1 = 17 
    
    for(int i=0; i<n; ++i)
        cin >> arr[i]; 
    cout << "Количество интересных пар: " << count_pairs(arr, 0, arr.size()-1) << endl;
}
