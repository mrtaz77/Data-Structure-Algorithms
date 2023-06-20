#include<bits/stdc++.h>
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

        if(!vis[u]){
            vis[u] = 1;

            for(auto x:adj[u]){
                int v = x.first;
                double weight = x.second;

                if(!vis[v] && keys[v] > weight){
                    parents[v] = u;
                    keys[v] = weight;
                    minHeap.push({keys[v],v});
                }
            }
        }
    }

    for(int i=0;i<n;i++){
        if(parents[i] != -1){
            mst.push_back({parents[i],{i,keys[i]}});
        }
    }
    return mst;
}
double mstCost(vector<pair<int,double>> adj[],int n){
    double cost = 0.0;
    vector<pair<int,pair<int,double>>> prim_mst = primMST(adj,n,0);

    for(int i = 0; i < prim_mst.size(); ++i)cost+=prim_mst[i].second.second;
    return cost;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    vector<pair<int,int>> co_ords;
    vector<pair<int,double>> *adj = new vector<pair<int,double>>[n];

    cin>>n;
    for(int i = 0; i < n; ++i){
        int x,y;
        cin>>x>>y;
        co_ords.push_back({x,y});
    }

    for(int i = 0; i < n-1; ++i){
        for(int j = i+1; j < n;j++){
            int u = i;
            int v = j;
            double d = abs(co_ords[i].first - co_ords[j].first) + abs(co_ords[i].second - co_ords[j].second);
            addEdge(adj,i,j,d);
            addEdge(adj,j,i,d);
        }
    }
    //print(adj,n);

    //vector<pair<int,pair<int,double>>> prim_mst = primMST(adj,n);

    cout<<mstCost(adj,n)<<endl;

    // for(int i = 0; i < prim_mst.size(); ++i){
    //     int u,v,w;
    //     u = prim_mst[i].first;
    //     v = prim_mst[i].second.first;
    //     cout<<u<<" "<<v<<endl; 
    // }

    delete[] adj;
}

/*
Prim-jarnik's algorithm works better than
kruskal's algorithm for dense graphs.And this
graph is a complete graph .
*/