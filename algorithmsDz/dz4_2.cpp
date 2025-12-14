#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <chrono>
#include <algorithm>

using namespace std;
mt19937 mt(time(nullptr));

vector<string> gen(int count) {
    vector<string> gen_vec(count);
    for(int i = 0; i < count; i++) {
        int ran_len = mt() % 1'0'00/*0'0*/ + 1;
        string word;
        for(int j = 0; j < ran_len; j++) {
            word += mt() % 26 + 65;
        }
        gen_vec[i] = word;
    }
    return gen_vec;
}

int max_len(vector<string> &vec) {
    int max_len = 0;
    for(string &word : vec) {
        if(word.length() > max_len) {
            max_len = word.length();
        }
    }
    return max_len;
}

void countingsort(vector<string> &vec, int ch_pos) {
    vector<int> freq(28, 0); // 90-65+1 'Z' - 'A' + 0 + 1(для пропуска) 27
    for(string &word : vec) {
        if(ch_pos < word.length()) {
            char cur_ch = word[ch_pos];
            freq[cur_ch - 'A' + 2]++;
        } else {
            char cur_ch = '@';
            freq[cur_ch - 'A' + 1]++;
        }
        
    }

    for(int i = 1; i < freq.size(); i++) { // префиксы
        freq[i] += freq[i-1];
    }

    vector<string> tempor(vec.size());
    for(int i = vec.size() - 1; i >= 0; i-- ) {
        char cur_ch;
        if(ch_pos < vec[i].length()) {
            cur_ch = vec[i][ch_pos];
            tempor[freq[cur_ch - 'A' + 2] - 1] = vec[i];
            freq[cur_ch - 'A' + 2]--;
        } else {
            cur_ch = '@';
            tempor[freq[cur_ch - 'A' + 1] - 1] = vec[i];
            freq[cur_ch - 'A' + 1]--;
        }
    }

    for(int i = 0; i < tempor.size(); i++ ) {
        vec[i] = tempor[i];
    }
}

void radixsort(vector<string> &vec) {
    int maxlen = max_len(vec);
    for(int ch_pos = maxlen; ch_pos >= 0; ch_pos--)
        countingsort(vec, ch_pos);
}

int main()
{
    //vector<string> vec = {"ZBC", "JLK", "ABCD", "FD", "A", "B", "NIBG"};
    cout << "number of strings " << endl;
    int count;
    cin >> count;

    vector<string> vec = gen(count);
    vector<string> vec_copy = vec;

    auto start = chrono::steady_clock::now();
    radixsort(vec);
    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_r = end - start;

    start = chrono::steady_clock::now();
    sort(vec_copy.begin(), vec_copy.end());
    end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_s = end - start;

    if(vec == vec_copy) {
        cout << "sort time " << elapsed_s.count() << " radix time " << elapsed_r.count() << endl;
    } else {
        cerr << "err " << endl;
    }

    /*for(int i = 0; i < vec.size(); i++) cout << vec[i] << " ";
    cout << endl << endl;
    for(int i = 0; i < vec.size(); i++) cout << vec_copy[i] << " "; */

    return 0;
}