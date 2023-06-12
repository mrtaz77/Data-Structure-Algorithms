#include<bits/stdc++.h>
#include"BFSDFS.h"
using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t;
    cin>>t;
    while(t--){
        int n,x,l,s;
        cin>>n>>x>>l;
        vector<pair<int,double>> *adj = new vector<pair<int,double>> [x];
        for(int i=0;i<l;i++){
            int u,v;
            cin>>u>>v;
            addEdge(adj,u,v);
        }
        cin>>s;
        for(int i=0;i<s;i++){
            int u,v;
            cin>>u>>v;
            addEdge(adj,u,v);
        }
        for(int i=0;i<x-1;i++){
            if(adj[i].size()==0)addEdge(adj,i,i+1);
        }
        print(adj,x);
        cout<<"================================================================\n";
    }
}