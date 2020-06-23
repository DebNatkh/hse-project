#include <vector>
#include <string>
#include <set>
#include "testlib.h"
#include <iostream>
using namespace std;


double score_test() {
    // if ()
    int n = inf.readInt(1, 10000, "n");
    int m = inf.readInt(1, 100, "m");
    vector<vector<int>> usage(m);
    for (int i = 0; i < m; i++) {
        int k = inf.readInt(1, n, "k_" + to_string(i+1));
        while (k--) {
            int x = inf.readInt(1, n);
            usage[i].push_back(x - 1);
        }
    }
    int ja = 0;
    vector<bool> used(n, false);
    int j_num = ans.readInt(1, m, "ans");
    for (int i = 0; i < j_num; i++) {
        int x = ans.readInt(1, m, "ans_" + to_string(i + 1)) - 1;
        for (auto e : usage[x]) {
            if (used[e]) {
                quitf(_fail, "jury answer has overlapping sets");
            }
            used[e] = 1;
            ja++;
        }
    }
    fill(used.begin(), used.end(), 0);
    int pa = 0;
    int p_num = ouf.readInt(1, m, "ans");
    for (int i = 0; i < p_num; i++) {
        int x = ouf.readInt(1, m, "ans_" + to_string(i + 1)) - 1;
        for (auto e : usage[x]) {
            if (used[e]) {
                pa = -1e9;
            }
            used[e] = 1;
            pa++;
        }
    }
    pa = max(0, pa);
    return pow((long double)pa / (long double)ja, 3) * 5.0;

}

int main(int argc, char **argv)
{
    registerTestlibCmd(argc, argv);
    int t = inf.readInt(1, 70, "n");
    double score = 0;
    while (t--) {
        score += score_test();
    }
    quitp(score, "participant's solution is ok");

    return 0;
} 