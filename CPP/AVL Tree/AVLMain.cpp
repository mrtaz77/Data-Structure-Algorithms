#include<bits/stdc++.h>
#include"AVLNode.h"
#include"AVL.h"
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

    long double insert_time = 0.0;
    long double delete_time = 0.0;
    long double search_time = 0.0;
    long double traversal_time = 0.0;

    clock_t start, end;
    

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
                start = clock();
                root = tree->insert(root,input);
                end = clock();
                insert_time += (long double)(end - start) / CLOCKS_PER_SEC * 1000.0;
                out<<tree->show(root)<<"\n";
                break;
            case 'D':
                iss>>input;
                start = clock();
                root = tree->erase(root,input);
                end = clock();
                delete_time += (long double)(end - start) / CLOCKS_PER_SEC * 1000.0;
                out<<tree->show(root)<<"\n";
                break;
            case 'T':
                start = clock();
                inOrd = tree->inOrder(root);
                end = clock();
                traversal_time += (long double)(end - start) / CLOCKS_PER_SEC * 1000.0;
                out<<inOrd<<"\n";
                break;
            case 'F':
                iss>>input;
                start = clock();
                bool found = tree->find(root,input);
                end = clock();
                search_time += (long double)(end - start) / CLOCKS_PER_SEC * 1000.0;
                if(found)out<<"found\n";
                else out<<"not found\n";
                break;
        }
    }

    report<<"operation time(ms)"<<endl;
    report<<"insert "<<setprecision(8)<<insert_time<<endl;
    report<<"delete "<<setprecision(8)<<delete_time<<endl;
    report<<"search "<<setprecision(8)<<search_time<<endl;
    report<<"trav "<<setprecision(8)<<traversal_time<<endl;
    report<<"total "<<setprecision(8)<<insert_time+delete_time+traversal_time+search_time<<endl;

    delete root;
    delete tree;
    in.close();
    out.close();
    report.close();
}
