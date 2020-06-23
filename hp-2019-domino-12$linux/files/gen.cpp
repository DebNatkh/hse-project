#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

int LIM = 1e9;

/* Generates random tree. */
int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    string type = string(argv[3]);
    assert(type == "random" || type == "equal");
    if (argc > 4) LIM = atoi(argv[4]);

    cout << n << " " << k << endl;
    if (type == "random") {
        for (int i = 0; i < n; i++) {
            cout << rnd.next(-LIM, LIM) << " " << rnd.next(-LIM, LIM) << endl;
        }
    } else if (type == "equal") {
        int x = rnd.next(-LIM, LIM);
        for (int i = 0; i < n; i++) {
            cout << x << " " << x << endl;
        }
    }
}
