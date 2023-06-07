#include<bits/stdc++.h>
using namespace std;

double edgeWeight(vector<pair<int,double>> adj[],int u,int v){
    for(auto x:adj[u]){
        if(x.first==v){
            return x.second;
        }
    }
    return INFINITY;	
}

void rmEdge(vector<pair<int,double>> adj[],int u,int v){
    for(int i=0;i<adj[u].size();i++){
        if(adj[u][i].first == v)adj[u].erase(adj[u].begin()+i);
    }
}

void addEdge(vector<pair<int,double>> adj[],int u,int v,double w){
    if(edgeWeight(adj,u,v) == INFINITY)adj[u].push_back({v,w});
    else{
        rmEdge(adj,u,v);
        adj[u].push_back({v,w});
    }
}

void print(vector<pair<int,double>> adj[],int n){
    for(int i=0;i<n;i++){
        cout<<i<<" -> ";
        for(auto x:adj[i]){
            cout<<x.first<<"("<<x.second<<") ";
        }
        cout<<endl;
    }
}