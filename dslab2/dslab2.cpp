#include "dslab2.h"
using namespace std;

int main()
{
    LinearTable t;
    //cout << t.getTableSize() << endl;
    //cout << t.nextPrime(7);
    int flex = 1;
    for (int i = 0; i < 100; i++) {
        string bruh = "alexander" + to_string(flex);
        t.addObject(bruh, flex);
        flex = flex + 1;
    }
    t.displayTable();
    cout << t.getTableSize();
}
