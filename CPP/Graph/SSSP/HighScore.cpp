#include<bits/stdc++.h>
using namespace std;
void addEdge(vector<pair<int,long double>> adj[],int u,int v,long double w=1.0){adj[u].push_back({v,w});}

int solve(vector<pair<int,long double>> adj[],int n){
    vector<pair<int,long double>> bf(n,{-1,0});
    int k = -1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(auto x:adj[j]){
                if(bf[j].second + x.second < bf[x.first].second){
                    bf[x.first].second = bf[j].second + x.second;
                    bf[x.first].first = j;
                    if(i == n-1)k = x.first;
                }
            }
        }
    }
    if(k == -1){
        int max = bf[0].second;
        for(int i = 1; i < n;i++){
            if(bf[i].second < max)max = bf[i].second;
        }
        return -max;
    }
    else{
        return -1;
    }
}

int main(){
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n,m;
    cin >> n >> m;

    
    vector<pair<int,long double>> *adjBF = new vector<pair<int,long double>>[n];

    for (int i = 0; i < m; ++i){
        int u,v;
        long double w;
        cin >> u >> v >> w;
        //Maximize distance , so -w
        addEdge(adjBF,u-1,v-1,-w);
    }

    cout<<solve(adjBF,n); 
}