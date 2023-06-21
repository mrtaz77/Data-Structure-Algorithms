#include<bits/stdc++.h>
#include"GraphUtil.h"
#include"DisjointSet.h"
using namespace std;

vector<pair<int,pair<int,double>>> kruskalMST(vector<pair<int,double>> adk[],int n){
    vector<pair<int,pair<int,double>>> mst;
    DisjointSet set(n);

    vector<pair<double, pair<int, int>>> edges;
    for (int i = 0; i < n; i++) {
        for (auto edge : adk[i])edges.push_back({edge.second,{i, edge.first}});
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

double mstCost(vector<pair<int,double>> adk[],int n){
    double cost = 0.0;
    vector<pair<int,pair<int,double>>> kruskal_mst = kruskalMST(adk,n);

    for(int i = 0; i < kruskal_mst.size(); ++i)cost+=kruskal_mst[i].second.second;
    return cost;
}

vector<pair<int,pair<int,double>>> secondMST(vector<pair<int,double>> adk[],int n){
    vector<pair<int,pair<int,double>>> sec_mst;

    vector<pair<double, pair<int, int>>> edges;
    for (int i = 0; i < n; i++) {
        for (auto edge : adk[i]) {
            int u = i;                     
            int v = edge.first;           
            double weight = edge.second;   
            edges.push_back({weight, {u, v}});
        }
    }
    
    sort(edges.begin(),edges.end());

    auto mst = kruskalMST(adk,n);
    double mst_cost = mstCost(adk,n);
    double sec_cost = INFINITY;
    for(int i = 0; i < mst.size(); i++){
        int ui = mst[i].first;
        int vi = mst[i].second.first;
        double wi = mst[i].second.second;
        cout<<ui<<" "<<vi<<" ("<<wi<<")"<<endl;
        vector<pair<int,pair<int,double>>> temp_mst;
        DisjointSet set(n);
        double cost = 0.0;
        int count = 0;
        for(int k = 0; k < edges.size() && count != n-1; k++){
            int u = edges[k].second.first;
            int v = edges[k].second.second;
            double weight = edges[k].first;
            if((ui == u && vi == v && weight == wi) || (ui == v && vi == u && weight == wi)){
                cout<<u<<" "<<v<<" ("<<weight<<")"<<endl; 
                continue;
            }
            if (set.findUp(u) != set.findUp(v)) {
                //cout<<u<<" "<<v<<" ("<<weight<<")"<<endl; 
                temp_mst.push_back({u, {v, weight}});
                count++;
                cost += weight;
                set.UnionByRank(u, v);
            }
        }
        if(cost < sec_cost &&  cost > mst_cost){
            sec_cost = cost;
            sec_mst = temp_mst;
        }
        cout<<"================================================================\n";
    }

    return sec_mst;
}



int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n,m;
    cin >> n >> m;

    vector<pair<int,double>> *adk = new vector<pair<int,double>>[n];

    for (int i = 0; i < m; ++i){
        int u,v;
        double w;
        cin >> u >> v >> w;
        addEdge(adk,u,v,w);
        addEdge(adk,v,u,w);
    }

    vector<pair<int,pair<int,double>>> sec_mst = secondMST(adk,n);

    cout<<"Second Best MST:\n";

    double weight = 0.0;
    for(int i = 0; i < sec_mst.size(); ++i){
        int u,v;
        u = sec_mst[i].first;
        v = sec_mst[i].second.first;
        weight += sec_mst[i].second.second;
        cout<<u<<" "<<v<<endl; 
    }
    cout<<"Cost = "<<weight;

    delete[] adk;
}

