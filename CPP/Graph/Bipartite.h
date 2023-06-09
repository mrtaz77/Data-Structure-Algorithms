#include <bits/stdc++.h>
using namespace std;
bool bipartite(vector<pair<int,double>> adj[],int n){
    vector<int> color(n,0);
    vector<int>parent(n,-1);
    queue<int> q;
    for(int i=0;i<n;i++){
        if(color[i]==0){
            q.push(i);
            if(parent[i]==-1)color[i]=1;
            else color[i]=3 - color[parent[i]];
            while(!q.empty()){
                int v = q.front();
                q.pop();
                for(auto x:adj[v]){
                    if(color[v] == color[x.first])return false;
                    else if(color[x.first] == 0){
                        parent[x.first] = v;
                        color[x.first] = 3 - color[v];
                        q.push(x.first);
                    }
                }
            }
        }
    }
    return true;
}