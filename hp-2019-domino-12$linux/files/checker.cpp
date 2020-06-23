/**
 * Author: Deb Natkh Maxim (debnatkh@gmail.com)
 * Date: 10.11.2019
 */

#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int n, k;
vector<array<int, 2>> arr;

bool adjustent(pair<int, int> A, pair<int, int> B) {
    return (A.first == B.first and abs(A.second - B.second) == 1) or
           (A.second == B.second and abs(A.first - B.first) == 1);
}

template<enum TResult result>
inline long long readAndCheckAnswer(InStream& in) {
    vector<vector<pair<int, int>>> tiles(k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; ++j) {
            int x = in.readInt(0, k);
            if (x > 0) { tiles[x - 1].push_back({i, j}); }
        }
    }
    for (int i = 0; i < k; ++i) {
        if (tiles[i].size() != 2)
            quitf(result, "One of domino numbers (%d) occurs tore or less than twice", i + 1);
        if (!adjustent(tiles[i][0], tiles[i][1]))
            quitf(result, "Two equal numbers (%d) are not adjustent", i + 1);
    }
    long long sm = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) { sm += arr[i][j]; }
    }
    for (int i = 0; i < k; i++) {
        for (auto tile : tiles[i]) { sm -= arr[tile.first][tile.second]; }
    }
    return sm;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();
    arr.resize(n);
    for (int i = 0; i < n; ++i) {
        arr[i][0] = inf.readInt();
        arr[i][1] = inf.readInt();
    }

    long long pa = readAndCheckAnswer<_wa>(ouf);
    long long ja = readAndCheckAnswer<_fail>(ans);

    if (ja < pa) quitf(_wa, "Jury has better answer than participant:\nJury: %lld\nParticipant: %lld", ja, pa);
    if (ja > pa) quitf(_fail, "Participant has better answer than jury:\nJury: %lld\nParticipant: %lld", ja, pa);

    quitf(_ok, "n=%d", n);
}
