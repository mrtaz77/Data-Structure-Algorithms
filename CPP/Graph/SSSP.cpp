#include<bits/stdc++.h>
#include"GraphUtil.h"
using namespace std;

vector<vector<pair<int,double>>> ssspTree(vector<pair<int,double>> adj[],int n,int start){
    vector<vector<pair<int,double>>> sssp(n);
    priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>> minHeap;

    vector<double> distance(n,INFINITY);
    vector<int> parents(n,-1);

    distance[start] = 0;
    minHeap.push({0,start});
    

    while(!minHeap.empty()){
        int u = minHeap.top().second;
        double dis = minHeap.top().first;
        minHeap.pop();

        for(auto x:adj[u]){
            int v = x.first;
            double weight = x.second;

            if(weight + distance[u] < distance[v]){
                parents[v] = u;
                distance[v] = weight + distance[u];
                minHeap.push({distance[v],v});
            }
        }
    }
    // for(int i=0;i<distance.size();i++)cout << distance[i] << 
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
    for(int i=0;i<distance.size();i++)cout <<distance[i] <<" ";
    cout << endl;
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
    }
    int start ;
    cin >> start ;
    // print(adj,n);

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