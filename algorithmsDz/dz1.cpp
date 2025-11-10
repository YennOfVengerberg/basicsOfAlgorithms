#include <iostream>
#include <vector>
#include <ctime>
#include <random>

using namespace std;
int main()
{
    mt19937 mt;
    int size;
    cin >> size;
    vector<int> vec(size);
    for(int i = 0; i < vec.size(); i++) vec[i] = mt();

    for(int i = 0; i < vec.size(); i++ ) cout << vec[i] << " ";
    cout << endl;

    for(int i = 1; i < vec.size(); i++) {
        if(i % 2 != 0) {
            if (vec[i] > vec[i-1]) swap(vec[i], vec[i-1]);
        } else {
            if (vec[i] < vec[i-1]) swap(vec[i], vec[i-1]);
        }
    }
    // a > b > c > d
    // a > c < b > d
    //
    //
    for(int i = 0; i < vec.size(); i++ ) cout << vec[i] << " ";
}