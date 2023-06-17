#include<bits/stdc++.h>
#include"GraphUtil.h"
#include"DisjointSet.h"
using namespace std;

bool compare(const pair<double, pair<int, int>>& a, const pair<double, pair<int,int>>& b) {
    return a.first > b.first;  // Compare in descending order
}


int delEdgeCount(vector<pair<int,double>> adj[],int n,int e){
    vector<pair<int,pair<int,double>>> mst;
    DisjointSet male(n),female(n);
    int count = 0;
    int maleV = 0;
    int femaleV = 0;

    vector<pair<double, pair<int, int>>> edges(e);
    for (int i = 0; i < n; i++) {
        for (auto edge : adj[i]) {
            int u = i;                     
            int v = edge.first;           
            double weight = edge.second;   
            edges.push_back({weight, {u, v}});
        }
    }

    sort(edges.begin(), edges.end(),compare);

    int i = 0;
    for(; i < e; i++) {
        if(edges[i].first != 3)break;
        else{
            int u = edges[i].second.first;
            int v = edges[i].second.second;
            if (male.findUp(u) != male.findUp(v) && female.findUp(u) != female.findUp(v)) {
                male.UnionByRank(u,v);
                female.UnionByRank(u,v);
                maleV++;
                femaleV++;
            }
            else {
                count++;
            }
        }
    }

    // mst for males
    for(; i < e; i++){
        if(edges[i].first != 2)break;
        else{
            int u = edges[i].second.first;
            int v = edges[i].second.second;
            if (male.findUp(u) != male.findUp(v)) {
                male.UnionByRank(u, v);
                maleV++;
            }
            else count++;
        }
    }

    for(; i < e; i++){       
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        if (female.findUp(u) != female.findUp(v)) {
            female.UnionByRank(u, v);
            femaleV++;
        }
        else count++;
    }
    if(maleV != n-1 || femaleV != n-1)return -1;
    return count;
}

int main(){

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n,m,start;
    cin>>n>>m;
    vector<pair<int,double>> *adj = new vector<pair<int,double>>[n];
    for(int i=0;i<m;i++){
        int u,v;
        double w;
        cin>>u>>v>>w;
        addEdge(adj,u-1,v-1,w);
    }
    print(adj,n);
    cout<<delEdgeCount(adj,n,m)<<endl;
}