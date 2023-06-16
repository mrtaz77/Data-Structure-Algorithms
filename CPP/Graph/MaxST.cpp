#include<bits/stdc++.h>
#include"GraphUtil.h"
using namespace std;

vector<pair<int,pair<int,double>>> maxST(vector<pair<int,double>> adj[],int n,int start){
    vector<pair<int,pair<int,double>>> maxST;
    priority_queue<pair<double,int>,vector<pair<double,int>>,less<pair<double,int>>> maxHeap;

    vector<double> keys(n,-INFINITY);
    vector<int> parents(n,-1);
    vector<int> vis(n,0);

    keys[start] = 0;
    maxHeap.push({0,start});

    while(!maxHeap.empty()){
        int u = maxHeap.top().second;
        maxHeap.pop();

        if(vis[u] == 0){

            vector<pair<int,double>> :: iterator itr;
            vis[u] = 1;

            for(itr=adj[u].begin();itr!=adj[u].end();itr++){
                int v = itr->first;
                double weight = itr->second;

                if(vis[v] == 0 && keys[v] < weight){
                    parents[v] = u;
                    keys[v] = weight;
                    maxHeap.push({keys[v],v});
                }
            }
        }
    }

    for(int i=0;i<n;i++){
        if(parents[i] != -1){
            maxST.push_back({parents[i],{i,edgeWeight(adj,parents[i],i)}});
        }
    }
    return maxST;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n,m;
    cin >> n >> m;

    vector<pair<int,double>> *adj = new vector<pair<int,double>>[n];

    for (int i = 0; i < m; ++i){
        int u,v;
        double w;
        cin >> u >> v >> w;
        addEdge(adj,u,v,w);
        addEdge(adj,v,u,w);
    }
    int start;
    cin >> start;
    print(adj,n);

    vector<pair<int,pair<int,double>>> prim_maxST = maxST(adj,n,start);
    double cost = 0.0;

    cout<<"List of edges selected for MaxST:\n{";

    
    for(int i = 0; i < prim_maxST.size(); ++i){
        int u,v,w;
        u = prim_maxST[i].first;
        v = prim_maxST[i].second.first;
        w = prim_maxST[i].second.second;
        cost += w;
        if(edgeWeight(adj,u,v) == w)cout<<"("<<u<<","<<v<<")";
        else cout<<"("<<v<<","<<u<<")"; 
    }
    cout<<"}\n";
    cout<<"Cost: "<<cost<<endl;
}