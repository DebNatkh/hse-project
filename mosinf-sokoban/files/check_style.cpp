#include <vector>
#include <string>
#include <set>
#include "testlib.h"
#include <iostream>
using namespace std;


double score_test() {
    int p_length = ouf.readInt(1, 1e9, "ans_length");
    for (int i = 0; i < p_length; i++) {
        string s = ouf.readToken("(Up|Left|Down|Right)", "move");
        cout << s << endl;
    }
    return 1 * 2.0;

}

int main(int argc, char **argv)
{
    registerTestlibCmd(argc, argv);
    int t = inf.readInt(1, 70, "t");
    double score = 0;
    while (t--) {
        score += score_test();
    }
    quitf(_ok, "participants solution is ok");

    return 0;
} 