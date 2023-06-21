#include<bits/stdc++.h>
#include"DisjointSet.h"
#include"GraphUtil.h"
using namespace std;

vector<pair<int,pair<int,double>>> kruskalMST(vector<pair<int,double>> adj[],int n){
    vector<pair<int,pair<int,double>>> mst;
    DisjointSet set(n);

    vector<pair<double, pair<int, int>>> edges;
    for (int i = 0; i < n; i++) {
        for (auto edge : adj[i])edges.push_back({edge.second,{i, edge.first}});
    }
    
    sort(edges.begin(),edges.end());

    for(auto e:edges){
        int u = e.second.first;
        int v = e.second.second;
        if (set.findUp(u) != set.findUp(v)) {
            mst.push_back({u, {v, e.first}});
            set.UnionByRank(u, v);
        }
    }

    return mst;
}

double mstCost(vector<pair<int,double>> adj[],int n){
    double cost = 0.0;
    vector<pair<int,pair<int,double>>> kruskal_mst = kruskalMST(adj,n);

    for(int i = 0; i < kruskal_mst.size(); ++i)cost+=kruskal_mst[i].second.second;
    return cost;
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("kruskal.txt", "w", stdout);

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
    //print(adj,n);

    vector<pair<int,pair<int,double>>> kruskal_mst = kruskalMST(adj,n);

    cout<<"Kruskal's Algorithm:\nTotal weight = "<<mstCost(adj,n)<<endl;

    
    for(int i = 0; i < kruskal_mst.size(); ++i){
        int u,v,w;
        u = kruskal_mst[i].first;
        v = kruskal_mst[i].second.first;
        cout<<u<<" "<<v<<endl; 
    }

    delete[] adj;
}