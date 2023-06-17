#include<bits/stdc++.h>
#include"GraphUtil.h"
#include"DisjointSet.h"
using namespace std;

vector<pair<int,int>> maxDegTree(vector<pair<int,double>> adj[],int n){
    vector<pair<int,int>> maxDeg;
    vector<int> indeg(n,0);
    DisjointSet set(n);

    int max = 0;
    for(int i = 0;i < n;i++){
        for(auto e:adj[i]){
            indeg[e.first]++;
            if(indeg[max] < indeg[e.first])max = e.first;
        }
    }

    for(auto x: adj[max]){
        int v = x.first;
        if(set.findUp(v) != set.findUp(max)){
            maxDeg.push_back({max,v});
            set.UnionByRank(max,v);
        }
    }

    for(int i = 0;i < n;i++){
        if(i == max)continue;
        for(auto x: adj[i]){
            int v = x.first;
            if(set.findUp(v) != set.findUp(i)){
                maxDeg.push_back({i,v});
                set.UnionByRank(i,v);
            }
        }
    }
    return maxDeg;
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
        cin >> u >> v ;
        addEdge(adj,u,v);
        addEdge(adj,v,u);
    }
    print(adj,n);

    vector<pair<int,int>> maxDeg = maxDegTree(adj,n);
    cout<<"List of edges of Maximum Degree Tree:\n{";
    
    for(int i = 0; i < maxDeg.size(); ++i){
        int u,v;
        u = maxDeg[i].first;
        v = maxDeg[i].second;
        cout<<"("<<u<<","<<v<<")"; 
    }
    cout<<"}\n";

    delete[] adj;

}