// #include "testlib.h"
#include <iostream>

using namespace std;

#include <iostream>
#include <string>
#include <algorithm>
#include <random>

std::default_random_engine generator;
void gen(int n, int m, int k) {;
    std::normal_distribution<double> distribution(k, rand() % 10);
    cout << n << " " << m << endl;
    for (int j = 0; j < m; j++) {
        int num = distribution(generator);
        num = max(num, 1);
        num = min(num, n);
        vector<int> arr(n);
        for (int i = 0; i < n; i++) arr[i] = i + 1;
        random_shuffle(arr.begin(), arr.end());
        cout << num;
        for (int i = 0; i < num; i++) {
            cout << " " << arr[i];
        }
        cout << endl;
    }

}

int main(int argc, char *argv[]) {
    generator.seed(57);
    int test_group = stoi(argv[1]);
    if (test_group == 1) {
        cout << 6 << endl;
        gen(5, 5, 3);
        gen(10, 10, 5);
        gen(20, 15, 5);
        gen(100, 20, 5);
        gen(100, 20, 10);
        gen(100, 20, 15);
    } else if (test_group == 2) {
        cout << 14 << endl;
        gen(20, 20, 4);
        gen(20, 40, 6);
        gen(20, 60, 8);
        gen(20, 100, 10);
        gen(20, 100, 10);
        gen(24, 100, 10);
        gen(10000, 10, 12);
        gen(10000, 11, 40);
        gen(1000, 30, 10);
        gen(1000, 60, 10);
        gen(1000, 60, 2);
        gen(9999, 100, 78);
        gen(10000, 100, 30);
    }
}