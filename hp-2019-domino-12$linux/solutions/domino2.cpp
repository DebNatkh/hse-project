#include <bits/stdc++.h>

using namespace std;

int n, k;

vector <pair <int, int>> v;
int a[2][100000];

int main()

{
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cin >> n >> k;
        for (int i = 0; i < n; ++i)
        {
                cin >> a[0][i] >> a[1][i];
                v.push_back({a[0][i] + a[1][i], i});
        }
        sort(v.begin(), v.end());
        reverse(v.begin(), v.end());
        int c = 1;
        for (int i = 0; i < k; i++)
        {
                int j = v[i].second;
                a[0][j] = c;
                a[1][j] = c;
                c++;
        }
        for (int i = k; i < n; i++)
        {
                int j = v[i].second;
                a[0][j] = 0;
                a[1][j] = 0;
        }
        for (int i = 0; i < n; i++)
        {
                cout << a[0][i] << " " << a[1][i] << endl;
        }
}
