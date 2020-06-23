/**
 * Author: Deb Natkh Maxim (debnatkh@gmail.com)
 * Desc: Main correct solution, using dp[i][j][mask] -- i rows are covered with j domino tiles, mask describes the last
 * row
 */

#include <bits/stdc++.h>
#define int long long
#define x first
#define y second
#define getbit(x, i) (((x) >> (i)) & 1)
using namespace std;
typedef pair<int, int> pii;

const int MAXN = 2e5;
int arr[MAXN][2];
int answer[MAXN][2];

vector<vector<int>> dp[4]; // mask, i, j


int max(int a, int b, int c) {
	return max(max(a, b), c);
}

int max(int a, int b, int c, int d) {
	return max(max(a, b), max(c, d));
}

int equind(int x, int a, int b, int c, int d) {
	if (x == a) return 0;
	if (x == b) return 1;
	if (x == c) return 2;
	if (x == d) return 3;
	return -1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < 2; ++j) {
    		cin >> arr[i][j];
    	}
    }
    if (k == 0) {
    	for (int i = 0; i < n; i++) {
    		cout << "0 0\n";
    	}
    	return 0;
    }
    for (int i = 0; i < 4; i++) {
    	dp[i].resize(n, vector<int>(k + 1, -1e18));
    }
    dp[0][0][0] = 0;
    dp[3][0][1] = arr[0][0] + arr[0][1];

    for (int row = 1; row < n; row++) {
    	dp[0][row][0] = 0;
    	for (int num = 1; num <= k; num++) {
    		dp[0][row][num] = max(
    			dp[0][row-1][num],
    			dp[1][row-1][num],
    			dp[2][row-1][num],
    			dp[3][row-1][num]
    		);

    		dp[1][row][num] = max(
    			dp[0][row-1][num-1],
    			dp[2][row-1][num-1]
    		) + arr[row][0] + arr[row-1][0];

    		dp[2][row][num] = max(
    			dp[0][row-1][num-1],
    			dp[1][row-1][num-1]
    		) + arr[row][1] + arr[row-1][1];

    		dp[3][row][num] = max(
    			dp[0][row-1][num-1],
    			dp[1][row-1][num-1],
    			dp[2][row-1][num-1],
    			dp[3][row-1][num-1]
    		) + arr[row][0] + arr[row][1];
    	}
    }
    int ans = max(
    	dp[0][n-1][k],
    	dp[1][n-1][k],
    	dp[2][n-1][k],
    	dp[3][n-1][k]
    );
    int mask = 0;
    for (int i = 0; i < 4; i++) if (dp[i][n - 1][k] == ans) mask = i;

	int cur_row = n - 1;
	int cur_used = k;
	do {
		if (mask == 0) {
			if (cur_row) mask = equind(dp[mask][cur_row][cur_used], 
				dp[0][cur_row-1][cur_used], dp[1][cur_row-1][cur_used], dp[2][cur_row-1][cur_used], dp[3][cur_row-1][cur_used]);
		} else if (mask == 1) {
			int add = arr[cur_row][0] + arr[cur_row-1][0];
			answer[cur_row][0] = cur_used;
			answer[cur_row-1][0] = cur_used;

			if (cur_row) mask = equind(dp[mask][cur_row][cur_used] - add,
				dp[0][cur_row-1][cur_used-1], 2e18, dp[2][cur_row-1][cur_used-1], 2e18);

			cur_used--;
		} else if (mask == 2) {
			int add = arr[cur_row][1] + arr[cur_row-1][1];
			answer[cur_row][1] = cur_used;
			answer[cur_row-1][1] = cur_used;

			if (cur_row) mask = equind(dp[mask][cur_row][cur_used] - add,
				dp[0][cur_row-1][cur_used-1], dp[1][cur_row-1][cur_used-1], 2e18,  2e18);

			cur_used--;
		} else {
			int add = arr[cur_row][0] + arr[cur_row][1];
			answer[cur_row][0] = cur_used;
			answer[cur_row][1] = cur_used;
			if (cur_row) mask = equind(dp[mask][cur_row][cur_used] - add, 
				dp[0][cur_row-1][cur_used-1], dp[1][cur_row-1][cur_used-1], dp[2][cur_row-1][cur_used-1], dp[3][cur_row-1][cur_used-1]);
			cur_used--;
		}
		--cur_row;
	} while (cur_row >= 0 && cur_used > 0);
	for (int i = 0; i < n; i++) {
		cout << answer[i][0] << " " << answer[i][1] << endl;;
	}
    return 0;
}
