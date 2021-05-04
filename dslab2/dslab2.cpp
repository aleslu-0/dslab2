#include "dslab2.h"
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main()
{
    srand(time(NULL));
    LinearTable t;
    //cout << t.getTableSize() << endl;
    //cout << t.nextPrime(7);
    int flex = 0;
    //cout << t.djb2Hash("bruh");
    high_resolution_clock::duration totalTime(0);
    auto start = high_resolution_clock::now();

    for (int i = 0; i < 10000; i++) {
        int randn = rand() % (1000 - 100) + 100; //numbers between 100 and 999
        string bruh = to_string(randn);
        t.addObject(bruh, flex);
        flex = i;
    }

    auto end = high_resolution_clock::now();
    totalTime = totalTime + (end - start);

    t.displayTable(); //bruh, flex, iteration
    cout << t.getTableSize();
    cout << "\nNumber of collisions: " << t.getTotalCol() << "\n Length of longest collision chain: " << t.getColChain();
    cout << "\nTotal time elapsed: " << totalTime.count();
}
