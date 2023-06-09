#include<bits/stdc++.h>
#include"GraphUtil.h"
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

    cout<<"Topological sort : "<<endl;

    if(cycle(adj,n))cout<<"-1"<<endl;
    else{
        vector<int> sorted = topSort(adj,n);
        cout<<"{";
        for(int i=0;i<sorted.size();i++){
            cout<<sorted[i];
            if(i != sorted.size()-1)cout<<",";
        }
        cout<<"}\n";
    }

    cout<<"Kahn Topological sort : "<<endl;
    vector<int> sortedKahn = kahnTopSort(adj,n);
    if(sortedKahn.size() < n)cout<<"-1"<<endl;
    else{
        cout<<"{";
        for(int i=0;i<sortedKahn.size();i++){
            cout<<sortedKahn[i];
            if(i != sortedKahn.size()-1)cout<<",";
        }
        cout<<"}\n";
    }
    cout<<"All topological sortings are : \n";
    allTopSort(adj,n);

    delete[]adj;
}