#include<bits/stdc++.h>
#include"GraphUtil.h"
using namespace std;

vector<vector<pair<int,double>>> ssspTree(vector<pair<int,double>> adj[],int n,int start){
    vector<vector<pair<int,double>>> sssp(n);
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
    stack<int> s;
    for(int i=0;i<n;i++){
        if(parents[i] != -1){
            int v = i;
            do{
                s.push(parents[v]);
                v = parents[v];
            }while(parents[v] != -1);
            while(!s.empty()){
                int p = s.top();
                s.pop();
                if(!s.empty())sssp[i].push_back({p,edgeWeight(adj,p,s.top())});
                else sssp[i].push_back({p,edgeWeight(adj,p,i)});
            }
        }
    }
    return sssp;
}


int main(){

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

    auto sssp = ssspTree(adj,n,start);
    vector<double> dis(n,0);
    dis[start] = 0;

    for(int i=0;i<n;i++){
        if(i != start){
            for(auto x:sssp[i]){
                cout<<x.first<<" -> ";
                dis[i] += x.second;
            }
            cout<<i<<endl;
        }
        else cout<<"Root : "<<start<<endl;
    }

    for(int i=0;i<n;i++)cout<<dis[i]<<" ";
}