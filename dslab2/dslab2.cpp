#include "dslab2.h"
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

void linear(int i) {
    srand(time(NULL));
    LinearTable t(i);
    int flex = 0;
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

    //t.displayTable(); //bruh, flex, iteration
    cout << "-Using linear probing with " << t.getSize() << " items-";
    cout << "\nNumber of collisions: " << t.getTotalCol() << "\n Length of longest collision chain: " << t.getColChain();
    cout << "\nTotal time elapsed: " << totalTime.count() << "\n\n";
    //cout << t.getSize() << " and " << t.getTableSize() << endl;
    //cout << t.getPercentage() << endl;
}
void hopscotch(int i) {
    //bruh
}

int main()
{
    while (true) {
        int inp;
        cout << "Linear Probing or Hopscotch? (1/0) \n";
        cin >> inp;
        switch (inp) {
        case 1:
        {
            cout << "Linear chosen. Ascii or djb2 encoding? (1/0)\n";
            int enc;
            cin >> enc;
            if (enc == 1 || enc == 0)
                linear(enc);
            else
                cout << "No";

        }
        break;

        case 0:
        {
            cout << "Hopscotch chosen. Ascii or djb2 encoding? (1/0)\n";
            int enc;
            cin >> enc;
            if (enc == 1 || enc == 0)
                hopscotch(enc);
            else
                cout << "No";
        }
        break;

        default:
        {
            cout << "Sorry, there is no such task!" << "\n\n";
        }
        }
    }

}

