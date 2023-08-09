#include<bits/stdc++.h>
#include"BinMinHeap.h"
using namespace std;

int main(){
    ifstream in("in.txt");
    ofstream out("out.txt");

    if (!in) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    if (!out) {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    BinMinHeap<int>* binHeap = new BinMinHeap<int>();
    
    
    
    string line;
    while(getline(in, line)){
        istringstream iss(line);
        char cmd;
        string inOrd;
        int min;
        
        iss >> cmd;

        switch(cmd) {
            case 'I':
                iss>>min;
                binHeap->insert(min);
                break;
            case 'F':
                if(binHeap->len()==0){
                    out<<endl;
                    continue;
                }
                min = binHeap->findMin();
                out<<"Find-Min returned "<<min<<endl;
                break;
            case 'E':
                if(binHeap->len()==0){
                    out<<endl;
                    continue;
                }
                min = binHeap->extractMin();
                out<<"Extract-Min returned "<<min<<endl;
                break;
            case 'U':{
                BinMinHeap<int>* tempHeap = new BinMinHeap<int>();
                while(iss>>min){
                    tempHeap->insert(min);
                }
                binHeap->Union(tempHeap);
                break;
            }
            case 'P':
                out<<binHeap->print();
                break;
        }
    }

}
