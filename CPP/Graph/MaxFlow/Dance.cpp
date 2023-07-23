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
    // if(path.size()>0){
    //     cout<<"Augmented paths"<<endl;
    //     for(int i = 0; i < path.size();i++){cout<<path[i];if(i!=path.size()-1)cout<<" -> ";}
    //     cout<<endl;
    // }
    return path;
}

void numDancePairs(vector<pair<int,long long>> adj[],int s,int t,int nx,int ny){
    auto augPath = augmentUtil(adj,s,t);

    long long maxFlow = 0;
    while(augPath.size()){
        long long bottleNeck = 1e17;
        for(int i = 0; i < augPath.size()-1; i++){
            int u = augPath[i];
            int v = augPath[i+1];
            bottleNeck = min(bottleNeck,edgeWeight(adj,u,v));
        }

        
        cout<<augPath[1]-1<<" "<<augPath[2]-nx-1<<endl;

        for(int i = 0; i < augPath.size()-1; i++){
            int u = augPath[i];
            int v = augPath[i+1];
            long long cap = edgeWeight(adj,u,v);
            long long prevFlow = edgeWeight(adj,v,u);
            rmEdge(adj,u,v);
            addEdge(adj,u,v,cap-bottleNeck);
            rmEdge(adj,v,u);
            addEdge(adj,v,u,prevFlow+bottleNeck);
        }
        maxFlow += bottleNeck;
        augPath = augmentUtil(adj,s,t);
    }


    // print(adj,t+1);
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int m,n,nx,ny,np;
    cin>>m>>n>>nx>>ny>>np;

    vector<pair<int,int>> pairList(np,{-1,-1});

    for(int i=0;i<np;i++){
        cin>>pairList[i].first>>pairList[i].second;
    }

    int nodes = 2 + nx + ny ;
    vector<pair<int,long long>> *adj = new vector<pair<int,long long>>[nodes];
    
    for(int i=0;i<nx;i++){addEdge(adj,0,i+1,n);addEdge(adj,i+1,0,0);}
    for(int i=1;i<=ny;i++){addEdge(adj,nx+i,nodes-1,n);addEdge(adj,nodes-1,nx+i,0);}
    for(int i=0;i<np;i++){
        addEdge(adj,pairList[i].first+1,nx+1+pairList[i].second,m);
        addEdge(adj,nx+1+pairList[i].second,pairList[i].first+1,0);
    }

    // print(adj,nodes);
    // cout<<endl;

    numDancePairs(adj,0,nodes-1,nx,ny);
}