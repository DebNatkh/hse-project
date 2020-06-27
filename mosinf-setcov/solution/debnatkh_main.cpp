#include <bits/stdc++.h>

// #define x first
// #define y second
#define hashset unordered_set<int>
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

// Struct for test information
struct input {
    int n, m;
    vector<vector<int>> sets;
};



// Read single test from stdin
input read_test() {
    input I;
    cin >> I.n >> I.m;
    I.sets.resize(I.m);
    for (int i = 0; i < I.m; i++) {
        int k;
        cin >> k;
        I.sets[i].resize(k);
        for (int j = 0; j < k; ++j) {
            cin >> I.sets[i][j];
            I.sets[i][j]--;
        }
    }
    return I;
}

// Print solution into stdout
void display(pair <int, vector<int>> A) {
    cout << A.second.size() << "\n";
    for (auto e : A.second) {
        cout << e + 1 << " ";
    }
    cout << endl;
}

// Brutforce solutuin O(m*2^n/64)
pair <int, vector<int>> brutforce_solve(input I) {
    const int MAXN = 1000;
    const int MAXM = 20;

    int n = I.n, m = I.m;
    if (n > MAXN || m > MAXM) {
        return {0, {}};
    }
    bitset<MAXN> masks[MAXM];
    int k[MAXM];


    for (int i = 0; i < m; i++) {
        k[i] = I.sets[i].size();
        masks[i].reset();
        for (int j = 0; j < k[i]; j++) {
            int x = I.sets[i][j] + 1;
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


    pair <int, vector<int>> answ;
    answ.first = __builtin_popcount(ans_mask);
    for (int i = 0; i < m; i++) {
        if (getbit(ans_mask, i)) {
            answ.second.push_back(i);
        }
    }
    return answ;
}

// Randomised brutforce solution
pair <int, vector<int>> brutforce_random(input I) {
    pair <int, vector<int>> answer = {0, {}};
    vector<int> order;
    for (int i = 0; i < I.m; ++i) {
        order.push_back(i);
    }
    for (int iter = 0; iter < 10; iter++) {
        random_shuffle(order.begin(), order.end());
        int new_size = min(I.m, 20);
        input J = {I.n, new_size, {}};
        for (int i = 0; i < new_size; i++) {
            J.sets.push_back(I.sets[order[i]]);
        }
        auto ans = brutforce_solve(J);
        for (int i = 0; i < ans.second.size(); i++) {
            ans.second[i] = order[ans.second[i]];
        }
        answer = max(answer, ans);
    }

    return answer;
}

// Annealing
pair <int, vector<int>> annealing(input I) {
    unordered_set<int> current = {};
    unordered_set<int> taken = {};
    
    int ITERS = 10000;

    for (int iter = 0; iter < ITERS; iter++) {

        int x = random() % I.m;
        
        if (taken.count(x)) {
            if (random() % ITERS < iter) {
                taken.erase(x);
                for (auto e : I.sets[x]) {
                    current.erase(e);
                }
            }
        } else {
            if (random() % ITERS < iter) {
        
                bool out = true;
                for (auto e : I.sets[x]) {
                    out = (current.count(e) == 0) && out;
                }
                if (out) {
                    taken.insert(x);
                    for (auto e : I.sets[x]) {
                        current.insert(e);
                    }
                }
            }
        }
    }

    pair <int, vector<int>> answer = {current.size(), vector<int>(taken.begin(), taken.end())};

    return answer;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        input I = read_test();
        auto ans = max(max(
            brutforce_solve(I),
            brutforce_random(I)),
            annealing(I)
        );
        display(ans);
    }

    return 0;
}