#include<bits/stdc++.h>
#include"AVLNode.h"
#include"AVL.h"
#include<chrono>
using namespace std;

int main(){
    ifstream in("in.txt");
    ofstream out("out.txt");
    ofstream report("report_avl.txt");

    if (!in) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    if (!out) {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    if (!report) {
        cerr << "Error opening report file." << endl;
        return 1;
    }

    AVL<int> *tree = new AVL<int>();
    AVLNode<int> *root = NULL;

    double insert_time = 0.0;
    double delete_time = 0.0;
    double search_time = 0.0;
    double traversal_time = 0.0;
    
    chrono::time_point<chrono::high_resolution_clock> start,end;

    string line;
    while(getline(in, line)){
        istringstream iss(line);
        char cmd;
        int input;
        string inOrd;
        
        iss >> cmd;

        switch(cmd) {
            case 'I':
                iss>>input;
                start = chrono::high_resolution_clock::now();
                root = tree->insert(root,input);
                end = chrono::high_resolution_clock::now();
                insert_time += chrono::duration_cast<chrono::duration<double,milli>>(end - start).count();
                out<<tree->show(root)<<"\n";
                break;
            case 'D':
                iss>>input;
                start = chrono::high_resolution_clock::now();
                root = tree->erase(root,input);
                end = chrono::high_resolution_clock::now();
                delete_time += chrono::duration_cast<chrono::duration<double,milli>>(end - start).count();
                out<<tree->show(root)<<"\n";
                break;
            case 'T':
                start = chrono::high_resolution_clock::now();
                inOrd = tree->inOrder(root);
                end = chrono::high_resolution_clock::now();
                traversal_time += chrono::duration_cast<chrono::duration<double,milli>>(end - start).count();
                out<<inOrd<<"\n";
                break;
            case 'F':
                iss>>input;
                start = chrono::high_resolution_clock::now();
                bool found = tree->find(root,input);
                end = chrono::high_resolution_clock::now();
                search_time += chrono::duration_cast<chrono::duration<double,milli>>(end - start).count();
                if(found)out<<"found\n";
                else out<<"not found\n";
                break;
        }
    }

    report<<"operation time(ms)"<<fixed<<setprecision(8)<<endl;
    report<<"insert "<<insert_time<<endl;
    report<<"delete "<<delete_time<<endl;
    report<<"search "<<search_time<<endl;
    report<<"trav "<<traversal_time<<endl;
    report<<"total "<<insert_time+delete_time+traversal_time+search_time<<endl;

    delete root;
    delete tree;
    in.close();
    out.close();
    report.close();
}
