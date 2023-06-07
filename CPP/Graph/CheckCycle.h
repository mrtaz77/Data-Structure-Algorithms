#include <bits/stdc++.h>
using namespace std;
bool cycleUtil(vector<pair<int,double>> adj[],int v,vector<bool>reVisit,vector<bool> visited){
    if(reVisit[v])return true;
    if(visited[v])return false;

    reVisit[v] = true;
    visited[v] = true;

    for(auto x:adj[v]){
        if(cycleUtil(adj,x.first,reVisit,visited))return true;
    }
    return reVisit[v] = false;
}

bool cycle(vector<pair<int,double>> adj[],int n){
    vector<bool> reVisit(n,false);
    vector<bool> visited(n,false);

    for(int i=0;i<n;i++){
        if(cycleUtil(adj,i,reVisit,visited))return true;
    }
    return false;
}
