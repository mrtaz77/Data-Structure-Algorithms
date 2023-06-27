#include<bits/stdc++.h>
using namespace std;
long double edgeWeight(vector<pair<int,long double>> adj[],int u,int v){
    long double weight = 1e17;
    for(auto x:adj[u]){
        if(x.first==v && x.second < weight){
            weight = x.second;
        }
    }
    return weight;	
}

void rmEdge(vector<pair<int,long double>> adj[],int u,int v){
    for(int i=0;i<adj[u].size();i++){
        if(adj[u][i].first == v)adj[u].erase(adj[u].begin()+i);
    }
}

void addEdge(vector<pair<int,long double>> adj[],int u,int v,long double w=1.0){adj[u].push_back({v,w});}

void print(vector<pair<int,long double>> adj[],int n){
    for(int i=0;i<n;i++){
        cout<<i<<" -> ";
        for(auto x:adj[i]){
            cout<<x.first<<"("<<x.second<<") ";
        }
        cout<<endl;
    }
}