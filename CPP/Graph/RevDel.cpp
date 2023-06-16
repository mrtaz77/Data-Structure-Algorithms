#include<bits/stdc++.h>
#include"GraphUtil.h"
using namespace std;

bool compare(const pair<double, pair<int, int>>& a, const pair<double, pair<int,int>>& b) {
    return a.first > b.first;  // Compare in descending order
}

int connectedComponents(const vector<pair<int,double>> adj[],int n){
    int num = 0;
    vector<bool> vis(n,false);
    queue<int> q;

    for(int i=0;i<n;i++){
        if(!vis[i]){
            num++;
            q.push(i);
            while(!q.empty()){
                int v = q.front();
                q.pop();
                vis[v] = true;
                for(auto x : adj[v]){
                    if(!vis[x.first])q.push(x.first);
                }
            }
        }
    }
    return num;
}

vector<pair<int,pair<int,double>>> revDel(vector<pair<int,double>> adj[],int n){
    vector<pair<int,pair<int,double>>> mst;
    vector<pair<double, pair<int, int>>> edges;
    for (int i = 0; i < n; i++) {
        for (auto edge : adj[i]) {
            int u = i;                     
            int v = edge.first;           
            double weight = edge.second;   
            edges.push_back({weight, {u, v}});
        }
    }
    
    sort(edges.begin(),edges.end(),compare);

    for(int i = 0; i < edges.size(); i++) {
        int u = edges[i].second.first; 
        int v = edges[i].second.second;
        double weight = edges[i].first; 

        rmEdge(adj,u,v);
        if(connectedComponents(adj,n)!=1){
            addEdge(adj,u,v,weight);
            mst.push_back({u,{v,weight}});
        }
    }
    return mst;
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
        addEdge(adj,u,v,w);
        addEdge(adj,v,u,w);
    }
    print(adj,n);

    vector<pair<int,pair<int,double>>> rev_del = revDel(adj,n);
    double cost = 0.0;

    cout<<"List of edges selected by Reverse Delete Algorithm: \n{";
    
    for(int i = 0; i < rev_del.size(); ++i){
        int u,v,w;
        u = rev_del[i].first;
        v = rev_del[i].second.first;
        w = rev_del[i].second.second;
        cost += w;
        if(edgeWeight(adj,u,v) == w)cout<<"("<<u<<","<<v<<")";
        else cout<<"("<<v<<","<<u<<")"; 
    }
    cout<<"}\n";
    cout<<"Cost: "<<cost<<endl;
}