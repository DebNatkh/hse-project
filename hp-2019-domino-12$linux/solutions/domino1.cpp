#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 3e5;
const int inf = 1e13;

int n, k;
int g[2][N], used[2][N];

signed main () {
#ifdef _IANE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;

    for (int i = 0; i < n; ++i)
        cin >> g[0][i] >> g[1][i];

    for (int i = 0; i < k; ++i) {
        int minn = -inf;
        int x1, y1, x2, y2;

        for (int j = 0; j < n; ++j) {
            if (used[0][j] || used[1][j])
                continue;
            if (g[0][j] + g[1][j] > minn) {
                minn = g[0][j] + g[1][j];
                x1 = 0, y1 = j;
                x2 = 1, y2 = j;
            }
        }

        for (int j = 1; j < n; ++j) {
            if (!used[0][j] && !used[0][j - 1]) {
                if (g[0][j] + g[0][j - 1] > minn) {
                    x1 = 0, y1 = j;
                    x2 = 0, y2 = j - 1;
                    minn = g[0][j] + g[0][j - 1];
                }
            }
            if (!used[1][j] && !used[1][j - 1]) {
                if (g[1][j] + g[1][j - 1] > minn) {
                    x1 = 1, y1 = j;
                    x2 = 1, y2 = j - 1;
                    minn = g[1][j] + g[1][j - 1];
                }
            }
        }

        used[x1][y1] = i + 1;
        used[x2][y2] = i + 1;
    }

    for (int i = 0; i < n; ++i)
        cout << used[0][i] << " " << used[1][i] << "\n";


    return 0;
}
