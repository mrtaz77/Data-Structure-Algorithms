#include <bits/stdc++.h>
using namespace std;

void topSortUtil(vector<pair<int,double>>adj[],stack<int> &s,vector<bool> &visited,int v){
    visited[v] = true;
    for(auto x:adj[v]){
        if(!visited[x.first])topSortUtil(adj,s,visited,x.first);
    }
    s.push(v);
}

stack<int> topSort(vector<pair<int,double>>adj[],int n){
    stack<int> s;
    vector<bool> visited(n,false);
    for(int i=0;i<n;i++){
        if(!visited[i]){
            visited[i] = true;
            for(auto x : adj[i]){
                if(!visited[x.first])topSortUtil(adj,s,visited,x.first);
            }
            s.push(i);
        }
    }
    return s;
}