#include <bits/stdc++.h>

using namespace std;

#define F first
#define S second
typedef long long   ll;
typedef long double ld;
typedef pair<ll, ll> pll;

ifstream in;
ofstream out;

const long long kk = 1000;
const long long ml = kk * kk;
const long long mod = ml * kk + 7;
const long long inf = ml * ml * ml + 7;


ll n, i, j, k;
vector<vector<vector<ll>>> dp;
vector<pll> m;
bool viv = false;


int main() {
//    viv = true;
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> k;
    for (i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
 /**
        a = 2 ^ (i & 1);
        b = 5 - a;
        b -= i / 3;
// **/
        m.push_back({a, b});
    }
    dp.resize(k + 2);
    for (auto &l : dp) {
        l.resize(n + 1);
        for (auto &sl : l)
            sl.resize(4);
    }

    dp[0][0][0] = 0;
    dp[0][0][1] = m[0].F;
    dp[0][0][2] = m[0].S;
    dp[0][0][3] = m[0].F + m[0].S;
    dp[1][0][0] = inf;
    dp[1][0][1] = inf;
    dp[1][0][2] = inf;
    dp[1][0][3] = 0;
    for (ll num = 2; num <= k; num++) {
        for (ll j = 0; j < 4; j++)
        dp[num][0][j] = inf;
    }
    for (ll i = 1; i < n; i++) {
        dp[0][i][0] = dp[0][i-1][3];
        dp[0][i][1] = dp[0][i][0] + m[i].F;
        dp[0][i][2] = dp[0][i][0] + m[i].S;
        dp[0][i][3] = dp[0][i][0] + m[i].F + m[i].S;
        if (viv) {
            cout << "For " << 0 << " dom's and " << i << " used: ";
            for (ll j = 0; j < 4; j++) {
                cout << dp[0][i][j] << ' ';
            }
            cout << endl;
        }
    }
    for (ll num = 1; num <= k; num++) {
        for (ll i = 1; i < n; i++) {
            dp[num][i][0] = dp[num][i-1][3];
            dp[num][i][1] = dp[num][i][0] + m[i].F;
            dp[num][i][2] = dp[num][i][0] + m[i].S;
            dp[num][i][3] = dp[num][i][0] + m[i].F + m[i].S;
            if (num) {
                dp[num][i][1] = min(dp[num][i][1], dp[num-1][i-1][2]);
                dp[num][i][2] = min(dp[num][i][2], dp[num-1][i-1][1]);
                dp[num][i][3] = min(dp[num][i][3], dp[num-1][i-1][3]);
            }
            if (viv) {
                cout << "For " << num << " dom's and " << i << " used: ";
                for (ll j = 0; j < 4; j++) {
                    cout << dp[num][i][j] << ' ';
                }
                cout << endl;
            }
            dp[num][i][3] = min(dp[num][i][3], dp[num][i][1] + m[i].S);
            dp[num][i][3] = min(dp[num][i][3], dp[num][i][2] + m[i].F);
        }
    }
    ll ans[2][n];
    for (ll i = 0; i < n; i++)
        ans[0][i] = 0,
        ans[1][i] = 0;
    ll now = n - 1;
    ll sm = 3;
    ll left = k;
    ll cnt = 1;

    if (viv)
        cout << "DP has worked" << endl;

    while (left) {
        if (viv)
            cout << "At start " << left << ' ' << now << ' ' << sm << endl;
        if (sm == 3) {
            if (now == 0 || dp[left][now][3] == dp[left-1][now-1][3]) {
                ans[0][now] = cnt;
                ans[1][now] = cnt;
                if (viv) {
                    cout << "Mark full " << now << endl;
                }
                cnt++;
                left--;
                now--;
            } else {
                if (dp[left][now][3] == dp[left][now-1][3] + m[now].F + m[now].S) {
                    now--;
                } else {
                    if (dp[left][now][1] + m[now].S == dp[left][now][3])
                        sm = 1;
                    else
                        if (dp[left][now][2] + m[now].F == dp[left][now][3])
                            sm = 2;
                }
            }
        } else {
            if (sm == 1) {
                if (dp[left][now][1] == dp[left - 1][now - 1][2]) {
                    ans[0][now] = cnt;
                    ans[0][now - 1] = cnt;
                    if (viv)
                        cout << "Mark left " << now - 1 << ' ' << now << endl;
                    cnt++;
                    left--;
                    now--;
                    sm = 2;
                } else {
                    if (dp[left][now][1] == dp[left][now - 1][3] + m[now].F) {
                        now--;
                        sm = 3;
                    }
                }
            } else {
                if (sm == 2) {
                    if (dp[left][now][2] == dp[left - 1][now - 1][1]) {
                        ans[1][now] = cnt;
                        ans[1][now - 1] = cnt;
                        if (viv)
                            cout << "Mark right " << now - 1 << ' ' << now << endl;
                        cnt++;
                        left--;
                        now--;
                        sm = 1;
                    } else {
                        if (dp[left][now][2] == dp[left][now - 1][3] + m[now].S) {
                            now--;
                            sm = 3;
                        }
                    }
                }
            }
        }
        if (viv)
            cout << "At finish " << left << ' ' << now << ' ' << sm << endl;
    }

    for (ll i = 0; i < n; i++)
        cout << ans[0][i] << ' ' << ans[1][i] << '\n';




    return 0;
}
/**
3 0
-3 2
2 -3
-3 2

11 10
1 99
99 99
99 99
99 99
-99 99
99 99
99 99
99 99
99 99
99 99
99 1


**/
