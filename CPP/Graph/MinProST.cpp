#include<bits/stdc++.h>
#include"GraphUtil.h"
#include"DisjointSet.h"
using namespace std;


vector<pair<int,pair<int,double>>> kruskalMST(vector<pair<int,double>> adj[],int n,int e){
    vector<pair<int,pair<int,double>>> mst;
    DisjointSet set(n);

    vector<pair<double, pair<int, int>>> edges(e);
    for (int i = 0; i < n; i++) {
        for (auto edge : adj[i]) {
            int u = i;                     
            int v = edge.first;           
            double weight = log(edge.second);   
            edges.push_back({weight, {u, v}});
        }
    }
    
    sort(edges.begin(),edges.end());

    for(auto e:edges){
        int u = e.second.first;
        int v = e.second.second;
        if (set.findUp(u) != set.findUp(v)) {
            mst.push_back({u, {v, e.first}});
            set.Union(u, v);
        }
    }

    return mst;
}


int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n,m;
    double cost;
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
    // print(temp,n);

    vector<pair<int,pair<int,double>>> kruskal_mst = kruskalMST(adj,n,m);
    cost = 1.0;

    cout<<"List of edges selected by Kruskal's: {";

    
    for(int i = 0; i < kruskal_mst.size(); ++i){
        int u,v,w;
        u = kruskal_mst[i].first;
        v = kruskal_mst[i].second.first;
        w = kruskal_mst[i].second.second;
        cost *= edgeWeight(adj,u,v);
        cout<<"("<<u<<","<<v<<")"; 
    }
    cout<<"}\n";
    cout<<"Cost: "<<cost<<endl;

    delete[] adj;
}