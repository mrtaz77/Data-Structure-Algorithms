#include<bits/stdc++.h>
#include"BFSDFS.h"
using namespace std;

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

    cout<<"Connected components : "<<connectedComponents(adj,n)<<endl;

}