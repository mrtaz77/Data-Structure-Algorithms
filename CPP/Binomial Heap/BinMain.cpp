#include<bits/stdc++.h>
#include"BinMinHeap.h"
using namespace std;

int main(){
    BinMinHeap<int>* binHeap = new BinMinHeap<int>();

    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        char cmd;
        int min;

        iss >> cmd;

        switch (cmd) {
            case 'I':
                iss >> min;
                binHeap->insert(min);
                break;
            case 'F':
                if (binHeap->len() == 0) {
                    cout << endl;
                    continue;
                }
                min = binHeap->findMin();
                cout << "Find-Min returned " << min << endl;
                break;
            case 'E':
                if (binHeap->len() == 0) {
                    cout << endl;
                    continue;
                }
                min = binHeap->extractMin();
                cout << "Extract-Min returned " << min << endl;
                break;
            case 'U': {
                BinMinHeap<int>* tempHeap = new BinMinHeap<int>();
                while (iss >> min) {
                    tempHeap->insert(min);
                }
                binHeap->Union(tempHeap);
                break;
            }
            case 'P':
                cout << binHeap->print();
                break;
        }
    }

}
