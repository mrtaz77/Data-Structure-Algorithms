#include<bits/stdc++.h>
#include"GraphUtil.h"
using namespace std;

vector<int> augmentUtil(vector<pair<int,long long>> adj[],int s,int t){
    vector<int> path;

    vector<bool>visited(t+1,false);
    vector<int>parent(t+1,-1);
    
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(auto x:adj[v]){
            if(!(visited[x.first] || edgeWeight(adj,v,x.first) <= 0)){
                q.push(x.first);
                parent[x.first] = v;
                visited[x.first] = true;
            }
        }
    }
    if(visited[t]){
        int pre = t;
        do{
            path.push_back(pre);
            pre = parent[pre];
            if(pre == s)path.push_back(pre);
        }while(pre != s);
        reverse(path.begin(),path.end());
    }
    // cout<<"Augmented paths"<<endl;
    // for(int i = 0; i < path.size();i++){cout<<path[i];if(i!=path.size()-1)cout<<" -> ";}
    // cout<<endl;
    return path;
}

vector<pair<int,int>> minCutUtil(vector<pair<int,long long>>adj[],int n,int start){
    vector<pair<int,int>> minCut;
    vector<int>bfsVert;
    vector<bool>visited(n,false);
    vector<int>parent(n,-1);
    vector<double>dist(n,INFINITY);
    dist[start] = 0;
    queue<int>q;
    q.push(start);
    visited[start] = true;
    bfsVert.push_back(start);
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(auto x:adj[v]){
            if(!(visited[x.first] || edgeWeight(adj,v,x.first) <= 0)){
                q.push(x.first);
                parent[x.first] = v;
                dist[x.first] = dist[v] + edgeWeight(adj,v,x.first);
                bfsVert.push_back(x.first);
                visited[x.first] = true;
            }
        }
    }
    // for(int i = 0; i < bfsVert.size();i++)cout<<bfsVert[i]<<" ";
    // cout<<endl;
    for(int i=0;i<bfsVert.size();i++){
        // cout<<bfsVert[i]<<" : ";
        for(auto x:adj[bfsVert[i]]){
            // cout<<x.first<<" ";
            if(!visited[x.first] && edgeWeight(adj,bfsVert[i],x.first)==0){
                minCut.push_back({bfsVert[i],x.first});
            }
        }
        // cout<<endl;
    }
    return minCut;
}

void maxFlow(vector<pair<int,long long>> adj[],int n,int s,int t){
    auto augPath = augmentUtil(adj,s,t);

    long long maxFlow = 0;
    while(augPath.size()){
        long long bottleNeck = 1e17;
        for(int i = 0; i < augPath.size()-1; i++){
            int u = augPath[i];
            int v = augPath[i+1];
            bottleNeck = min(bottleNeck,edgeWeight(adj,u,v));
        }

        
        for(int i = 0; i < augPath.size()-1; i++){
            int u = augPath[i];
            int v = augPath[i+1];
            long long cap = edgeWeight(adj,u,v);
            long long prevFlow = edgeWeight(adj,v,u);
            rmEdge(adj,u,v);
            addEdge(adj,u,v,cap-bottleNeck);
            rmEdge(adj,v,u);
            if(prevFlow == 1e17)prevFlow = 0;
            addEdge(adj,v,u,prevFlow+bottleNeck);
        }
        maxFlow += bottleNeck;
        augPath = augmentUtil(adj,s,t);
    }
    cout<<maxFlow<<endl;
    // print(adj,n);

    auto minCut = minCutUtil(adj,n,s);  

    for(int i=0;i<minCut.size();i++)cout<<minCut[i].first<<" -> "<<minCut[i].second<<endl;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n,m;
    cin >> n >> m;
    
    vector<pair<int,long long int>> *adj = new vector<pair<int,long long int>>[n];

    for (int i = 0; i < m; ++i){
        int u,v;
        long long int w;
        cin >> u >> v >> w;
        long long int prevWeight = edgeWeight(adj,u,v);
        rmEdge(adj,u,v);
        if(prevWeight == 1e17)prevWeight = 0;
        addEdge(adj,u,v,w+prevWeight);
        // if(edgeWeight(adj,v,u)==1e17)addEdge(adj,v,u,0);
    }
    // print(adj,n);
    maxFlow(adj,n,0,n-1);
}
