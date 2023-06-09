#include<bits/stdc++.h>
#include"BFSDFS.h"
#include"CheckCycle.h"
#include"TopSort.h"
using namespace std;
int main(){

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);


    int n,m,start;
    cin>>n>>m;
    vector<pair<int,double>> *adj = new vector<pair<int,double>>[n];
    for(int i=0;i<m;i++){
        int u,v;
        double w;
        cin>>u>>v>>w;
        addEdge(adj,u,v,w);
    }
    print(adj,n);

    cin>>start;

    vector<pair<int,int>> bfsTree = BFStraversal(adj,n,start);
    
    cout<<"BFS Tree : \n";


    for(int i=0;i<bfsTree.size();i++){
        int v = bfsTree[i].first;
        cout<<v<<" -> ";
        while(bfsTree[i].first==v && i<bfsTree.size()){
            cout<<bfsTree[i].second;
            i = i+1;
            if(bfsTree[i].first == v && i<bfsTree.size())cout<<",";
        }
        i--;
        cout<<endl;
    }

    vector<pair<int,int>> bfsAll = BFSAll(adj,n);
    

    cout<<"BFS all :\n";

    for(int i=0;i<bfsAll.size();i++){
        int v = bfsAll[i].first;
        cout<<v<<" -> ";
        while(bfsAll[i].first==v && i<bfsAll.size()){
            cout<<bfsAll[i].second;
            i = i+1;
            if(bfsAll[i].first == v && i<bfsAll.size())cout<<",";
        }
        i--;
        cout<<endl;
    }

    vector<pair<int,int>> dfsTree = DFSTraversal(adj,n,start);
    
    cout<<"DFS Tree : \n";

    for(int i=0;i<dfsTree.size();i++){
        int v = dfsTree[i].first;
        cout<<v<<" -> ";
        while(dfsTree[i].first==v && i<dfsTree.size()){
            cout<<dfsTree[i].second;
            i = i+1;
            if(dfsTree[i].first == v && i<dfsTree.size())cout<<",";
        }
        i--;
        cout<<endl;
    }

    vector<pair<int,int>> dfsAll = DFSAll(adj,n);
    

    cout<<"DFS all :\n";

    for(int i=0;i<dfsAll.size();i++){
        int v = dfsAll[i].first;
        cout<<v<<" -> ";
        while(dfsAll[i].first==v && i<dfsAll.size()){
            cout<<dfsAll[i].second;
            i = i+1;
            if(dfsAll[i].first == v && i<dfsAll.size())cout<<",";
        }
        i--;
        cout<<endl;
    }

    cout<<"Cycle : "<<boolalpha<<cycle(adj,n)<<endl;

    cout<<"Topological sort : "<<endl;

    vector<int> sorted = topSort(adj,n);
    cout<<"{";
    for(int i=0;i<sorted.size();i++){
        cout<<sorted[i];
        if(i != sorted.size()-1)cout<<",";
    }
    cout<<"}";

    delete[]adj;
}