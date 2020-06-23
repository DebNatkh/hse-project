#include <bits/stdc++.h>

#define llong long long

using namespace std;

int main(void)
{
    llong n = 0, k = 0, p = 0, ans = 0, x = 0, y = 0, z = 0;
    bool u = false;
    cin >> n >> k;
    vector<pair<llong, llong> > a(n, {0, 0});
    vector<vector<pair<llong, llong> > > b(n + 1, vector<pair<llong, llong> > (k + 1, {0, -1}));
    vector<pair<llong, llong> > ansm(n + 1, {0, 0});
    for (llong i = 0; i < n; i++)
    {
        cin >> a[i].first >> a[i].second;
    }
    for (llong i = 1; i <= n; i++)
    {
        for (llong j = 1; j <= k && j <= i + 1; j++)
        {
            x = b[i - 1][j - 1].first + a[i - 1].first + a[i - 1].second;
            y = (i < 2)?0:a[i - 2].first + a[i - 1].first + b[i - 2][j - 1].first;
            z = (i < 2)?0:a[i - 2].second + a[i - 1].second + b[i - 2][j - 1].first;
            if (x > y)
            {
                if (x > z)
                {
                    b[i][j] = {x, 0};
                    // x
                }
                else
                {
                    b[i][j] = {z, 2};
                    // z
                }
            }
            else
            {
                if (y > z)
                {
                    b[i][j] = {y, 1};
                    // y
                }
                else
                {
                    b[i][j] = {z, 2};
                    // z
                }
            }
        }
    }
    for (llong i = 0; i <= n; i++)
    {
        if (b[i].back().first > ans)
        {
            ans = b[i].back().first;
            p = i;
        }
    }
    p--;
    u = true;
    for (llong i = k; p >= 0 && u; i--)
    {
        u = true;
        switch(b[p + 1][i].second)
        {
        case 0:
            ansm[p] = {i, i};
            p--;
            break;
        case 1:
            ansm[p].first = i;
            ansm[p - 1].first = i;
            p -= 2;
            break;
        case 2:
            ansm[p].second = 1;
            ansm[p - 1].second = 1;
            p -= 2;
            break;
        default:
            u = false;
            break;
        }
    }
    for (llong i = 0; i < n; i++)
    {
        cout << ansm[i].first << ' ' << ansm[i].second << '\n';
    }
    return 0;
}
