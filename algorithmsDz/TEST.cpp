#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>
#include <cstdlib>
using namespace std;
// Функция для генерации случайных строк
mt19937 mt(time(nullptr));

std::vector<std::string> generateRandomStrings(int n) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> disLength(1, 10'000); // Длина строки <= 10k
    std::uniform_int_distribution<> disChar('a', 'z');   // Строка из малых латинских букв

    std::vector<std::string> result;
    for (int i = 0; i < n; ++i) {
        auto strLen = disLength(gen);
        std::string s(strLen, '\0');
        std::generate_n(s.begin(), strLen, [&]() { return disChar(gen); });
        result.push_back(s);
    }
    return result;
}

void countingSortByPosition(std::vector<std::string>& arr, size_t position) {
    const int alphabetSize = 28; // ASCII letters ('a'-'z') plus special character for padding

    std::vector<int> freq(alphabetSize, 0);
    std::vector<std::string> temp(arr.size());

    // Подсчитываем частоту встречаемости символов
    for (const auto& s : arr) {
        char ch = (position < s.length()) ? s[position] : '$'; // Используем символ "$" для отсутствующих позиций
        freq[ch - 'a' + 1]++;
    }

    // Преобразуем частоту в индексы для распределения
    for (size_t i = 1; i < alphabetSize; ++i) {
        freq[i] += freq[i - 1];
    }

    // Заполняем временный массив упорядоченными элементами
    for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
        char ch = (*it)[position]; // Берём символ текущего положения
        temp[--freq[(ch - 'a' + 1)]].swap(*it);
    }

    // Копируем обратно в исходный массив
    arr.swap(temp);
}

void radixSort(std::vector<std::string>& arr) {
    size_t maxLen = 0;
    for (const auto& s : arr) {
        maxLen = std::max(maxLen, s.length()); // Найдем максимальную длину строки
    }

    // Сортируем строки построчно, начиная с последней позиции
    for (size_t pos = maxLen - 1; pos < maxLen; --pos) {
        countingSortByPosition(arr, pos);
    }
}

void standardSort(std::vector<std::string>& arr) {
    std::sort(arr.begin(), arr.end());
}

template<typename Func>
double measureTime(Func func, std::vector<std::string>& data) {
    auto start = std::chrono::high_resolution_clock::now();
    func(data);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

int main() {
   for(int i = 0; i < 100; i++) cout << mt() % 26 + 65 << " ";

    return 0;
}