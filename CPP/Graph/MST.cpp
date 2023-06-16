#include<bits/stdc++.h>
#include"GraphUtil.h"
#include"DisjointSet.h"
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

vector<pair<int,pair<int,double>>> kruskalMST(vector<pair<int,double>> adj[],int n,int e){
    vector<pair<int,pair<int,double>>> mst;
    DisjointSet set(n);

    vector<pair<double, pair<int, int>>> edges(e);
    for (int i = 0; i < n; i++) {
        for (auto edge : adj[i]) {
            int u = i;                     
            int v = edge.first;           
            double weight = edge.second;   
            edges.push_back({weight, {u, v}});
        }
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
    // print(temp,n);

    cout<<"============================\n";

    vector<pair<int,pair<int,double>>> prim_mst = primMST(adj,n,start);
    double cost = 0.0;

    cout<<"List of edges selected by Prim's: {";

    
    for(int i = 0; i < prim_mst.size(); ++i){
        int u,v,w;
        u = prim_mst[i].first;
        v = prim_mst[i].second.first;
        w = prim_mst[i].second.second;
        cost += w;
        if(edgeWeight(adj,u,v) == w)cout<<"("<<u<<","<<v<<")";
        else cout<<"("<<v<<","<<u<<")"; 
    }
    cout<<"}\n";
    cout<<"Cost: "<<cost<<endl;

    cout<<"============================\n";

    vector<pair<int,pair<int,double>>> kruskal_mst = kruskalMST(adj,n,m);
    cost = 0.0;

    cout<<"List of edges selected by Kruskal's: {";

    
    for(int i = 0; i < kruskal_mst.size(); ++i){
        int u,v,w;
        u = kruskal_mst[i].first;
        v = kruskal_mst[i].second.first;
        w = kruskal_mst[i].second.second;
        cost += w;
        if(edgeWeight(adj,u,v) == w)cout<<"("<<u<<","<<v<<")";
        else cout<<"("<<v<<","<<u<<")"; 
    }
    cout<<"}\n";
    cout<<"Cost: "<<cost<<endl;

    delete[] adj;
}