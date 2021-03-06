#include "dslab2.h"
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

void linear(int i) {
    srand(time(0));
    LinearTable t(i);
    high_resolution_clock::duration totalTime(0);
    auto start = high_resolution_clock::now();

    for (int i = 0; i < 10000; i++) {
        int randn = rand() % (1000 - 100) + 100; //numbers between 100 and 999
        string name = to_string(randn);
        t.addObject(name, i);       
    }

    auto end = high_resolution_clock::now();
    totalTime = totalTime + (end - start);

    //t.displayTable(); 
    cout << "\n-Using linear probing with " << t.getSize() << " items-";
    cout << "\nNumber of collisions: " << t.getTotalCol() << "\nLength of longest collision chain: " << t.getColChain();
    cout << "\nTotal time elapsed: " << totalTime.count() << " nanoseconds\n\n";
    //cout << t.getSize() << " and " << t.getTableSize() << endl;
    //cout << t.getPercentage() << endl;
}

void hopscotch(int i) {
    srand(time(0));
    HopScotchTable h(i);
    high_resolution_clock::duration totalTime(0);
    auto start = high_resolution_clock::now();

    for (int i = 0; i < 10000; i++) {
        
        string extra = to_string(rand());
		string name = to_string(rand()) + extra;
        h.addObject(name, i);
    }

    auto end = high_resolution_clock::now();
    totalTime = totalTime + (end - start);

    //h.displayTable(); 
    cout << "\n-Using hopscotch hashing with 10000 items-";
    cout << "\nNumber of collisions: " << h.getTotalCol() << "\nLength of longest collision chain: " << h.getColChain();
    cout << "\nTotal time elapsed: " << totalTime.count() << " nanoseconds\n\n";
    //cout << t.getSize() << " and " << t.getTableSize() << endl;
    //cout << t.getPercentage() << endl;
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
                cout << "Invalid";

        }
        break;

        case 0:
        {
            cout << "Hopscotch chosen. Sdbm or djb2 encoding? (1/0)\n";
            int enc;
            cin >> enc;
            if (enc == 1 || enc == 0)
                hopscotch(enc);
            else
                cout << "Invalid";
        }
        break;

        default:
        {
            cout << "Sorry, there is no such task!" << "\n\n";
        }
        }
    }
    return 0;
}

