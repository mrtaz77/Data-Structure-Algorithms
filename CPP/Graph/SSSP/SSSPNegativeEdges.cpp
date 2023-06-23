// Vjudge problem Single Source Shortest Path (Negative Edges) 
// Find only those negative weight cycles which are reachable from starting node
// No need to consider other negative weight cycles

#include<bits/stdc++.h>
using namespace std;
void addEdge(vector<pair<int,long long>> adj[],int u,int v,long long w=1){adj[u].push_back({v,w});}

vector<pair<int,long long>>bellFord(vector<pair<int,long long>> adj[],int n,int start){
    vector<pair<int,long long>> bf(n,{-1,INT_MAX});
    bf[start].second = 0.0;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n;j++){
            for(auto x:adj[j]){
                if(bf[j].second + x.second < bf[x.first].second){
                    bf[x.first].second = bf[j].second + x.second;
                    bf[x.first].first = j;
                }
            }
        }
    }
    for(int j=0;j<n;j++){
        for(auto x:adj[j]){
            if(bf[j].second + x.second < bf[x.first].second){
                bf.clear();
                return bf;
            }
        }
    }
    return bf;
}


void print(vector<pair<int,long long>> adj[],int n){
    for(int i=0;i<n;i++){
        cout<<i<<" -> ";
        for(auto x:adj[i]){
            cout<<x.first<<"("<<x.second<<") ";
        }
        cout<<endl;
    }
}

int main(){

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n,m,s;
    cin >> n >> m>>s;
    vector<pair<int,long long>> *adjBF = new vector<pair<int,long long>>[n];
    for (int i = 0; i < m; ++i){
        int u,v;
        long long w;
        cin >> u >> v >> w;
        addEdge(adjBF,u,v,w);
    }
    // print(adjBF,n);

    auto bf = bellFord(adjBF,n,s);
    if(bf.size()==0){
        cout<<"NEGATIVE CYCLE"<<endl;
    }
    else{
        for(int i=0;i<n;i++){
            if(bf[i].second == INT_MAX) cout<<"INF"<<endl;
            else cout<<bf[i].second<<endl;
        }
    }
}