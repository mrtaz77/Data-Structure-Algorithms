#include <bits/stdc++.h>
#include"GraphUtil.h"
using namespace std;

vector<pair<int,int>> BFStraversal(vector<pair<int,double>>adj[],int n,int start){
    vector<pair<int,int>>bfsTree;
    vector<bool>visited(n,false);
    vector<int>parent(n,-1);
    vector<double>dist(n,INFINITY);
    dist[start] = 0;
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
                dist[x.first] = dist[v] + edgeWeight(adj,v,x.first);
                bfsTree.push_back({v,x.first});
                visited[x.first] = true;
            }
        }
    }
    // for(int i=0;i<n;i++)cout<<parent[i]<<" ";
    // cout<<endl;
    // for(int i=0;i<n;i++)cout<<dist[i]<<" ";
    // cout<<endl;

    return bfsTree;
}

vector<pair<int,int>> BFSAll(vector<pair<int,double>>adj[],int n){
    vector<pair<int,int>>bfsTree;
    vector<bool>visited(n,false);
    vector<int>parent(n,-1);
    vector<double>dist(n,INFINITY);
    queue<int>q;

    for(int i=0;i<n;i++){
        if(!visited[i]){
            dist[i] = 0;
            q.push(i);
            visited[i] = true;
            while(!q.empty()){
                int v = q.front();
                q.pop();
                for(auto x:adj[v]){
                    if(!visited[x.first]){
                        q.push(x.first);
                        parent[x.first] = v;
                        dist[x.first] = dist[v] + edgeWeight(adj,v,x.first);
                        bfsTree.push_back({v,x.first});
                        visited[x.first] = true;
                    }
                }
            }
        }
    }


    
    // for(int i=0;i<n;i++)cout<<parent[i]<<" ";
    // cout<<endl;
    // for(int i=0;i<n;i++)cout<<dist[i]<<" ";
    // cout<<endl;

    return bfsTree;
}

void DFSUtil(vector<pair<int,double>> adj[],vector<pair<int,int>> &dfsTree,vector<bool> &visited,vector<int> &parent,int v){
    visited[v] = true;
    for(auto x : adj[v]){
        if(!visited[x.first]){
            dfsTree.push_back({v,x.first});
            parent[x.first] = v;
            DFSUtil(adj,dfsTree,visited,parent,x.first);
        }
    }
}

vector<pair<int,int>> DFSTraversal(vector<pair<int,double>> adj[],int n,int start){
    vector<pair<int,int>> dfsTree;
    vector<bool>visited(n,false);
    vector<int>parent(n,-1);

    DFSUtil(adj,dfsTree,visited,parent,start);

    // for(int i=0;i<n;i++)cout<<parent[i]<<" ";
    // cout<<endl;

    return dfsTree;
}

vector<pair<int,int>> DFSAll(vector<pair<int,double>> adj[],int n){
    vector<pair<int,int>> dfsTree;
    vector<bool>visited(n,false);
    vector<int>parent(n,-1);

    for(int i=0;i<n;i++){
        if(!visited[i])DFSUtil(adj,dfsTree,visited,parent,i);
    }

    // for(int i=0;i<n;i++)cout<<parent[i]<<" ";
    // cout<<endl;

    return dfsTree;
}


