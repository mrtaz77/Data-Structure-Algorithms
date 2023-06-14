#include<bits/stdc++.h>
#include"BFSDFS.h"
using namespace std;

pair<int,int> bfs(vector<pair<int,double>>adj[],int n,int node){
    vector<bool> vis(n,false);
    vector<int> dis(n,-1);
    queue<int> q;
    q.push(node);
    dis[node]=0;
    vis[node] = true;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto x:adj[u]){
            if(!vis[x.first]){
                dis[x.first] = dis[u]+1;
                q.push(x.first);
                vis[x.first] = true;
            }
        }
    }

    int max = 0;
    int nodeIndex = 0;
    for(int i = 0; i < n;i++){
        if(dis[i] > max){
            max = dis[i];
            nodeIndex = i;

        }
    }
    return make_pair(nodeIndex,max);
}

vector<int> longestPath(vector<pair<int,double>> adj[],int n){
    vector<int> path;
    pair<int,int> p1,p2;
    p1 = bfs(adj,n,0);
    p2 = bfs(adj,n,p1.first);

    int start = p1.first;

    vector<bool>visited(n,false);
    vector<int>parent(n,-1);
    queue<int>q;
    q.push(start);
    visited[start] = true;
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(auto x:adj[v]){
            if(!visited[x.first]){
                q.push(x.first);
                parent[x.first] = v;
                visited[x.first] = true;
            }
        }
    }
    int v = p2.first;
    while(v != p1.first){
        path.push_back(v);
        v = parent[v];
    }
    path.push_back(p1.first);
    return path;
}

int main(){

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n,m,start;
    cin>>n;
    vector<pair<int,double>> *adj = new vector<pair<int,double>>[n];
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        addEdge(adj,u,v);
        addEdge(adj,v,u);
    }
    //print(adj,n);

    auto x = longestPath(adj,n);
    cout<<x.size()-1<<endl;

    for(int i=0;i<x.size();i++)cout<<x[i]<<" ";
}