#include<bits/stdc++.h>
using namespace std;
class DisjointSet{
    vector <int> rank,parent;
public:
    DisjointSet(int n){
        //handling both 0 and 1 based indexing graphs
        rank.resize(n+1,0);
        parent.resize(n+1);
        for(int i=0;i<=n;i++)parent[i]=i;
    }

    int findUp(int node){
        if(parent[node]!=node)parent[node]=findUp(parent[node]);
        return parent[node];
    }

    void Union(int x,int y){
        x=findUp(x);
        y=findUp(y);
        if(x!=y){
            if(rank[x]>rank[y])parent[y]=x;
            else{
                parent[x]=y;
                if(rank[x]==rank[y])rank[y]++;
            }
        }
    }
};