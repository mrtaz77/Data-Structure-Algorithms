#include<bits/stdc++.h>
#include"DisjointSet.h"
#include"GraphUtil.h"
using namespace std;

vector<pair<int,pair<int,double>>> primMST(vector<pair<int,double>> adj[],int n,int start){
    vector<pair<int,pair<int,double>>> mst;
    priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>> minHeap;

    vector<double> keys(n,INFINITY);
    vector<int> parents(n,-1);
    vector<int> vis(n,0);

    keys[start] = 0;
    minHeap.push({0,start});

    while(!minHeap.empty()){
        int u = minHeap.top().second;
        minHeap.pop();

        if(vis[u] == 0){

            vector<pair<int,double>> :: iterator itr;
            vis[u] = 1;

            for(itr=adj[u].begin();itr!=adj[u].end();itr++){
                int v = itr->first;
                double weight = itr->second;

                if(vis[v] == 0 && keys[v] > weight){
                    parents[v] = u;
                    keys[v] = weight;
                    minHeap.push({keys[v],v});
                }
            }
        }
    }

    for(int i=0;i<n;i++){
        if(parents[i] != -1){
            mst.push_back({parents[i],{i,edgeWeight(adj,parents[i],i)}});
        }
    }
    return mst;
}

double mstCost(vector<pair<int,double>> adj[],int n,int start){
    double cost = 0.0;
    vector<pair<int,pair<int,double>>> prim_mst = primMST(adj,n,start);

    for(int i = 0; i < prim_mst.size(); ++i)cost+=prim_mst[i].second.second;
    return cost;
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("prim.txt", "w", stdout);

    int n,m,start;
    cin >> n >> m;

    vector<pair<int,double>> *adj = new vector<pair<int,double>>[n];

    for (int i = 0; i < m; ++i){
        int u,v;
        double w;
        cin >> u >> v >> w;
        addEdge(adj,u,v,w);
        addEdge(adj,v,u,w);
    }
    start = 0;
    //print(adj,n);
    if(start<0 || start>=n){
        cout<<"Invalid root node.Using 0 as default."<<endl;
        start=0;
    }

    vector<pair<int,pair<int,double>>> prim_mst = primMST(adj,n,start);

    cout<<"Prim's Algorithm:\n";
    cout<<"Root node = "<<start<<endl;
    cout<<"Total weight = "<<mstCost(adj,n,start)<<endl;

    for(int i = 0; i < prim_mst.size(); ++i){
        int u,v,w;
        u = prim_mst[i].first;
        v = prim_mst[i].second.first;
        cout<<u<<" "<<v<<endl; 
    }

    delete[] adj;
}