#include <bits/stdc++.h>
using namespace std;

int rows, cols;
int crates_num = 0, fields_num = 0;
const int MAXN = 30;
char field[MAXN][MAXN];
bool dead_end[MAXN * MAXN];
int move_graph[MAXN * MAXN][4];
int mapping[MAXN][MAXN];
int mappingX[MAXN * MAXN];
int mappingY[MAXN * MAXN];
vector<int> targets_list;

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

/*
    State is a structure used in order to effectively store every state
   avaliable in the game. In this implementation pair<long long, long long> is
   used as uint8_t array of size 16. First element represents the position of
   sokoban, following crates_num numbers represent sorted position of crates. It
   is assumed, that number of empty cells on the field is less than 256,
   crates_num is less than
   8
*/
// typedef long long state;
// typedef array<unsigned char, 16> state;
typedef pair<long long, long long> state;

// const state zero_state = 0;
// const state zero_state = state();
const state zero_state = {0, 0};

const int max_state_crates = 15;

const int max_fields_num = 256;

/*
    get_state(S, 0) returns position of sokoban, get_state(S, i) returns the
   position of i-th crate
*/
inline int get_state(state S, int pos) {
    return ((unsigned char *)&S)[pos];
    // return S[pos];
}

/*
    set_state(S, 0, val) sets the position of sokoban as val, set_state(S, i,
   val) sets the position of i-th crate to val
*/
inline void set_state(state &S, int pos, int val) {
    ((unsigned char *)&S)[pos] = val;
    // S[pos] = val;
}

/*
    finds if there is a crate = val, return its position(0 otherwise)
*/
inline int check_state(state &S, int val) {
    unsigned char *arr = ((unsigned char *)&S);
    
    // for (int i = 1; i <= crates_num; ++i) {
    //     if (arr[i] == val) return i;
    // }
    // return 0;
    
    if (arr[1] > val) return 0;
    int left = 1, right = crates_num + 1;
    while (left + 1 < right) {
        int med = (left + right) / 2;
        if (arr[med] <= val) left = med;
        else right = med;
    }
    return (arr[left] == val) ? left : 0;
}

/*
    Auxilliary function used to maintain array of crates positions sorted
*/
inline void fix_state(state &S, int pos) {
    while (pos + 1 <= crates_num) {
        int L = get_state(S, pos);
        int R = get_state(S, pos + 1);
        if (L > R) {
            set_state(S, pos, R);
            set_state(S, pos + 1, L);
            ++pos;
        } else {
            break;
        }
    }
    while (pos - 1 >= 1) {
        int L = get_state(S, pos - 1);
        int R = get_state(S, pos);
        if (L > R) {
            set_state(S, pos - 1, R);
            set_state(S, pos, L);
            --pos;
        } else {
            break;
        }
    }
}

void display(state S) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char c = field[i][j];
            if (mapping[i][j] < 0) {
            } else {
                for (int p = 0; p <= crates_num; ++p) {
                    if (get_state(S, p) == mapping[i][j]) {
                        c = (p == 0 ? 'S' : 'B');
                    }
                }
            }
            cout << c;
        }
        cout << endl;
    }
}

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

/*
    Returns the state, which can be achieved by pushing sokoban in direction
   dir, where dir:

   * 0 = Right
   * 1 = Down
   * 2 = Left
   * 3 = Up
*/
inline state push(state S, int dir) {
    int x = mappingX[get_state(S, 0)];
    int y = mappingY[get_state(S, 0)];
    int nx = x + dx[dir];
    int ny = y + dy[dir];
    if (mapping[nx][ny] < 0) return zero_state;
    int pos = mapping[nx][ny];
    int i = check_state(S, pos);
    if (i) {
        int nnx = nx + dx[dir];
        int nny = ny + dy[dir];
        if (mapping[nnx][nny] < 0) return zero_state;
        int pos_crate = mapping[nnx][nny];

        if (check_state(S, pos_crate)) return zero_state;

        set_state(S, 0, pos);
        set_state(S, i, pos_crate);
        fix_state(S, i);
        return S;
    }
    set_state(S, 0, pos);
    return S;
}

inline state pull_release(state S, int dir) {
    int x = mappingX[get_state(S, 0)];
    int y = mappingY[get_state(S, 0)];
    int nx = x + dx[dir];
    int ny = y + dy[dir];
    if (mapping[nx][ny] < 0) return zero_state;
    int pos = mapping[nx][ny];
    if (check_state(S, pos)) return zero_state;
    set_state(S, 0, pos);
    return S;
}

inline state pull_hold(state S, int dir) {
    int x = mappingX[get_state(S, 0)];
    int y = mappingY[get_state(S, 0)];
    int nx = x + dx[dir];
    int ny = y + dy[dir];
    if (mapping[nx][ny] < 0) return zero_state;
    int pos = mapping[nx][ny];
    if (check_state(S, pos)) return zero_state;
    set_state(S, 0, pos);
    nx = x - dx[dir];
    ny = y - dy[dir];
    if (mapping[nx][ny] < 0) return zero_state;
    pos = mapping[nx][ny];
    int i = check_state(S, pos);
    if (i) {
        set_state(S, i, mapping[x][y]);
        fix_state(S, i);
    }
    return S;
}

inline bool is_dead_end(state& S) {
    for (int i = 1; i <= crates_num; i++) {
        if (dead_end[get_state(S, i)]) return 1;
    }
    return 0;
}

void precalc_dead_end() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (field[i][j] == '.') {
                for (int ang = 0; ang < 4; ang++) {
                    int ni = i + dx[ang];
                    int nj = j + dy[ang];

                    int nni = i + dx[(ang + 1) % 4];
                    int nnj = j + dy[(ang + 1) % 4];
                    if (field[ni][nj] == '#' && field[nni][nnj] == '#') {
                        dead_end[mapping[i][j]] = 1;
                    }
                }
            }
        }
    }
}

void precalc_move_graph() {
    for (int i = 0; i < fields_num; ++i) {
        int x = mappingX[i];
        int y = mappingY[i];
        for (int j = 0; j < 4; j++) {
            int nx = x + dx[j];
            int ny = y + dy[j];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                move_graph[i][j] = mapping[nx][ny];
            } else {
                move_graph[i][j] = mapping[nx][ny];
            }
        }
    }
}

inline bool is_term(state &S) {
    for (int i = 1; i <= crates_num; ++i) {
        if (get_state(S, i) != targets_list[i - 1]) return false;
    }
    // for (int i = 1; i <= crates_num; ++i) {
    //     int pos = get_state(S, i);
    //     if (field[mappingX[pos]][mappingY[pos]] != 'X') return false;
    // }
    return true;
}

int _main(bool skip = 0, int prob = 8) {
    // fprintf(stderr, "%s\n", argv[1]);

    cin >> rows >> cols;

    state start_pos = zero_state;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> field[i][j];
            if (field[i][j] != '#') {
                mapping[i][j] = fields_num;
                mappingX[fields_num] = i;
                mappingY[fields_num] = j;
                fields_num++;
            } else {
                mapping[i][j] = -1;
            }
        }
    }
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    set_state(start_pos, 0, mapping[x][y]);

    cin >> crates_num;

    assert(crates_num <= max_state_crates);
    assert(fields_num <= max_fields_num);

    vector<int> crates_list;
    for (int i = 0; i < crates_num; ++i) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        crates_list.push_back(mapping[x][y]);
    }

    for (int i = 0; i < crates_num; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        field[x][y] = 'X';
        targets_list.push_back(mapping[x][y]);
    }
    if (skip) {
        targets_list.clear();
        crates_list.clear();
        crates_num = 0;
        fields_num = 0;
        return 0;
    }
    sort(crates_list.begin(), crates_list.end());
    for (int i = 0; i < crates_num; ++i) {
        set_state(start_pos, i + 1, crates_list[i]);
    }
    sort(targets_list.begin(), targets_list.end());

    precalc_dead_end();
    precalc_move_graph();

    unordered_map<state, int, pair_hash> dist;
    unordered_map<state, int, pair_hash> back_dist;
    unordered_map<state, state, pair_hash> prev;
    unordered_map<state, state, pair_hash> back_prev;
    queue<state> Q;
    queue<state> backQ;
    Q.push(start_pos);

    dist[start_pos] = 0;
    prev[start_pos] = zero_state;
    state final = zero_state;
    state final_state = zero_state;
    for (int i = 1; i <= crates_num; ++i) {
        set_state(final_state, i, targets_list[i - 1]);
    }
    for (auto base : targets_list) {
        for (int d = 0; d < 4; d++) {
            int pos = move_graph[base][d];
            if (field[mappingX[pos]][mappingY[pos]] == '.') {
                set_state(final_state, 0, pos);
                back_dist[final_state] = 0;
                back_prev[final_state] = zero_state;
                backQ.push(final_state);
            }
        }
    }
    int prv0 = -1, prv1 = -1;

    int phase = 0;

    // cerr << endl;
    // display(start_pos);
    // cerr << endl;

    clock_t start, end;
    start = clock();

    while (!Q.empty() || !backQ.empty()) {
        if (phase) {
            if (!backQ.empty()) {
                state S = backQ.front();
                backQ.pop();
                if (dist.count(S)) {
                    final = S;
                    break;
                }
                for (int d = 0; d < 8; d++) {
                    state SS =
                        (d < 4 ? pull_hold(S, d) : pull_release(S, d - 4));
                    if (SS != zero_state) {
                        if (!back_dist.count(SS)) {
                            if (is_dead_end(SS)) {
                                back_dist[SS] = 1e9;
                            } else {
                                back_prev[SS] = S;
                                back_dist[SS] = back_dist[S] + 1;
                                backQ.push(SS);
                            }
                        }
                    }
                }
                if (prv0 < back_dist[S]) {
                    cerr << "0\t" << (prv0 = back_dist[S]) << "\n";
                }
            }
        } else {
            if (!Q.empty()) {
                state S = Q.front();
                Q.pop();
                if (back_dist.count(S)) {
                    final = S;
                    break;
                }
                for (int d = 0; d < 4; d++) {
                    state SS = push(S, d);
                    if (SS != zero_state) {
                        if (!dist.count(SS)) {
                            if (is_dead_end(SS)) {
                                dist[SS] = 1e9;
                            } else {
                                prev[SS] = S;
                                dist[SS] = dist[S] + 1;
                                Q.push(SS);
                            }
                        }
                    }
                }
                if (prv1 < dist[S]) {
                    cerr << "1\t" << (prv1 = dist[S]) << "\n";
                }
            }
        }

        // phase ^= 1;
        if (rand() % 16 < prob) {
            phase = 1;
        } else {
            phase = 0;
        }
    }

    cout << back_dist[final] + dist[final] << endl;
    cerr << back_dist[final] + dist[final] << endl;

    vector<int> positions;
    for (state S = prev[final]; S != zero_state; S = prev[S]) {
        positions.push_back(get_state(S, 0));
    }
    reverse(positions.begin(), positions.end());
    for (state S = final; S != zero_state; S = back_prev[S]) {
        positions.push_back(get_state(S, 0));
    }
    for (int i = 1; i < positions.size(); ++i) {
        int nx = mappingX[positions[i]];
        int ny = mappingY[positions[i]];
        int x = mappingX[positions[i - 1]];
        int y = mappingY[positions[i - 1]];
        if (x == nx) {
            if (y < ny) {
                cout << "Right\n";
            } else {
                cout << "Left\n";
            }
        } else {
            if (x < nx) {
                cout << "Down\n";
            } else {
                cout << "Up\n";
            }
        }
    }

    end = clock();
    cerr << fixed << setprecision(6)
         << double(end - start) / double(CLOCKS_PER_SEC) << endl;
    // cout << dist.size() << endl;
    // cout << prev.size() << endl;
}

int main(int argc, char const *argv[]) {
    freopen(argv[1], "r", stdin);
    int prob = (argc == 3 ? 8 : atoi(argv[3]));
    int test = atoi(argv[2]);
    int t;
    cin >> t;
    for (int i = 0; i < test; i++) {
        _main(1, prob);
    }
    _main(0, prob);

    fclose(stdin);
    return 0;
}