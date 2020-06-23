#include <bits/stdc++.h>

#define x first
#define y second
#define hashset unordered_set
#define hashmap unordered_map
#define getbit(x, i) (((x) >> (i)) & 1)
using namespace std;
typedef pair<int, int> pii;
template <typename T>
inline vector<T> readvector(size_t size) {
    vector<T> res(size);
    for (size_t i = 0; i < size; ++i) {
        cin >> res[i];
    }
    return res;
}
template <typename T>
inline void printvector(vector<T> &arr, string sep = " ", string ends = "\n") {
    for (size_t i = 0; i < arr.size(); ++i) {
    }
}
inline int binPow(int x, int deg, int mod) {
    int ans = 1;
    for (int i = sizeof(x) * CHAR_BIT - 1; i >= 0; i--) {
        ans *= ans;
        ans %= mod;
        if (getbit(deg, i)) ans *= x;
        ans %= mod;
    }
    return ans;
}

// =======================

#define MAXN 101
#define MAXM 20

bitset<MAXN> masks[MAXM];
int k[MAXM];

void solve() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        cin >> k[i];
        masks[i].reset();
        for (int j = 0; j < k[i]; j++) {
            int x;
            cin >> x;
            masks[i][--x] = 1;
        }
    }
    vector<int>order(m);
    for (int i = 0; i < m; i++) order[i] = i;
    int ans = 0;
    int ans_mask = 0;


    for (int mask = 0; mask < (1 << m); mask++) {
        bitset<MAXN> cur;
        cur.reset();

        int cnt = 0;
        for (int i = 0; i < m; i++) {
            if (getbit(mask, i)) {
                cnt += k[i];
                cur |= masks[i];
            }
        }

        if (cnt == cur.count()) {
            if (ans < cnt) {
                ans = cnt;
                ans_mask = mask;
            }
        }
    }


    cout << __builtin_popcount(ans_mask) << endl;
    for (int i = 0; i < m; i++) {
        if (getbit(ans_mask, i)) {
            cout << i + 1 << " ";
        }
    }
    cout << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}