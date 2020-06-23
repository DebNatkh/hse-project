#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "testlib.h"
using namespace std;
#define pii pair<int, int>

const int MAXN = 500;

map<string, pii> move_alias = {
    {"Up", {-1, 0}}, {"Down", {1, 0}}, {"Left", {0, -1}}, {"Right", {0, 1}}};

bool isCorrect(
    vector<string> field,
    int sokoX,
    int sokoY,
    int rows,
    int cols,
    vector<pii> moves,
    vector<pii> targets) {
    for (auto move : moves) {
        int nx = sokoX + move.first;
        int ny = sokoY + move.second;
        if (nx < 0 || ny < 0 || nx >= rows || ny >= cols) {
            return false;
        }
        if (field[nx][ny] == '.') {
            sokoX = nx;
            sokoY = ny;
        } else if (field[nx][ny] == '#') {
            // Cannot move sokoban
        } else {
            int nnx = nx + move.first;
            int nny = ny + move.second;
            if (nnx < 0 || nny < 0 || nnx >= rows || nny >= cols) {
                return false;
            }
            if (field[nnx][nny] == '.') {
                field[nnx][nny] = 'X';
                field[nx][ny] = '.';
                sokoX = nx;
                sokoY = ny;
            } else {
                // Cannot move crate
            }
        }
    }
    for (auto target : targets) {
        if (field[target.first][target.second] != 'X') {
            return false;
        }
    }
    return true;
}

double score_test() {
    int rows = inf.readInt(1, MAXN, "rows");
    int cols = inf.readInt(1, MAXN, "cols");

    vector<string> field(rows);
    for (int i = 0; i < rows; i++) {
        field[i] = inf.readToken();
    }
    int sokoX = inf.readInt(1, MAXN) - 1;
    int sokoY = inf.readInt(1, MAXN) - 1;

    int crateNum = inf.readInt(1, MAXN * MAXN);

    for (int i = 0; i < crateNum; i++) {
        int x = inf.readInt() - 1;
        int y = inf.readInt() - 1;
        field[x][y] = 'X';
    }
    vector<pii> targets;
    for (int i = 0; i < crateNum; i++) {
        int x = inf.readInt() - 1;
        int y = inf.readInt() - 1;
        targets.push_back({x, y});
    }

    int ansP = ouf.readInt(1, 1e9, "ans_length");
    vector<pii> moveP;
    for (int i = 0; i < ansP; i++) {
        string s = ouf.readToken("(Up|Left|Down|Right)", "move");
        moveP.push_back(move_alias[s]);
    }

    int ansJ = ans.readInt(1, 1e9, "ans_length");
    vector<pii> moveJ;
    for (int i = 0; i < ansJ; i++) {
        string s = ans.readToken("(Up|Left|Down|Right)", "move");
        moveJ.push_back(move_alias[s]);
    }

    bool correctP = isCorrect(field, sokoX, sokoY, rows, cols, moveP, targets);
    bool correctJ = isCorrect(field, sokoX, sokoY, rows, cols, moveJ, targets);

    if (!correctP) {
        return 0;
    }
    if (!correctJ) {
        quitp(_fail, "Jury answer is incorrect : target not achieved");
    }
    if (ansP < ansJ) quitp(_fail, "pa < ja");

    // cout << ansJ << " / " << ansP << endl;
    return pow((double)ansJ / (double)ansP, 4) * 2.0;
}

int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int t = inf.readInt(1, 70, "n");
    double score = 0;
    cout << t << endl;
    while (t--) {
        score += score_test();
    }
    quitp(score, "participant's solution is ok");

    return 0;
}