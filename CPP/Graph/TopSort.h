#include <bits/stdc++.h>
using namespace std;

void topSortUtil(vector<pair<int,double>>adj[],stack<int> &s,vector<bool> &visited,int v){
    visited[v] = true;
    for(auto x:adj[v]){
        if(!visited[x.first])topSortUtil(adj,s,visited,x.first);
    }
    s.push(v);
}

vector<int> topSort(vector<pair<int,double>>adj[],int n){
    stack<int> s;
    vector<bool> visited(n,false);
    for(int i=0;i<n;i++){
        if(!visited[i])topSortUtil(adj,s,visited,i);
    }
    vector<int> sort;
    while(!s.empty()){
        sort.push_back(s.top());
        s.pop();
    }
    return sort;
}

vector<int> kahnTopSort(vector<pair<int,double>>adj[],int n){
    vector<int> sorted;
    vector<int> indeg(n,0);

    for(int i=0;i<n;i++){
        for(auto x:adj[i]){
            indeg[x.first]++;
        }
    }

    queue<int> q;
    for(int i=0;i<n;i++){
        if(indeg[i] == 0){
            q.push(i);
        }
    }

    while(!q.empty()){
        int node = q.front();
        sorted.push_back(node);
        q.pop();
        for(auto x:adj[node]){
            indeg[x.first]--;
            if(indeg[x.first] == 0)q.push(x.first);
        }
    }
    return sorted;
}
