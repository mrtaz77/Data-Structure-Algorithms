#include<bits/stdc++.h>
#include"GraphUtil.h"
#include"TopSort.h"
#include"CheckCycle.h"
using namespace std;

vector<pair<int,int>> maxEdge(vector<pair<int,double>> adj[],int n){
    vector<int> sorted = topSort(adj,n);
    vector<pair<int,int>> edges;
    for(int i = 0; i < n-1; i++){
        for(int j = i+1; j < n; j++){
            if(edgeWeight(adj,sorted[i],sorted[j]) == INFINITY){
                edges.push_back({sorted[i],sorted[j]});
            }
        }
    }
    return edges;
}


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

    if(cycle(adj,n)){
        cout<<"Edges: "<<0<<endl;
        exit(1);
    }

    vector<pair<int,int>> edges = maxEdge(adj,n);
    cout<<"Edges: "<<edges.size()<<endl;
    for(int i=0;i<edges.size();i++){
        cout<<edges[i].first<<" -> "<<edges[i].second<<endl;
    }
}