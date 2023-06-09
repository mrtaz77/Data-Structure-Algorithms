#include <bits/stdc++.h>
#include "GraphUtil.h"
#include "Bipartite.h"
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
        addEdge(adj,v,u,w);
    }
    print(adj,n);

    cout<<"Bipartite: "<<boolalpha<<bipartite(adj,n);
}