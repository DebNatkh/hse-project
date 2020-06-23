#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const long long MAXN = 2e5;
const long long LIM = 1e9;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readInt(1, MAXN, "n");
    inf.readSpace();
    long long k = inf.readInt(0, MAXN, "k");
    inf.readEoln();
    ensuref(n * k <= MAXN, "n * m must be less or equal than %lld", MAXN);
    ensuref(n >= k, "n must be greater or equal than k");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; ++j) {
            inf.readInt(-LIM, LIM, "x[" + to_string(i) + "][" + to_string(j) + "]");
            if (j == 0) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }
    inf.readEof();
}
