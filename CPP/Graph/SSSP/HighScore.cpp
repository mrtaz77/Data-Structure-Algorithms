#include<bits/stdc++.h>
using namespace std;
void addEdge(vector<pair<int,long long int>> adj[],int u,int v,long long int w=1.0){adj[u].push_back({v,w});}

long long int solve(vector<pair<int,long long int>> adj[],int n){
    vector<pair<int,long long int>> bf(n,{-1,1e17});
    bf[0].second = 0;
    int k = -1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(auto x:adj[j]){
                if(bf[j].second != 1e17 && bf[j].second + x.second < bf[x.first].second){
                    bf[x.first].second = bf[j].second + x.second;
                    bf[x.first].first = j;
                    if(i == n-1)k = x.first;
                }
            }
        }
    }
    if(k != -1){
        bf[k].second = -1e17;
        for(int i=0;i<n-1;i++){
            for(int j=0;j<n;j++){
                for(auto x:adj[j]){
                    if(bf[j].second != 1e17 && bf[j].second + x.second < bf[x.first].second){
                        bf[x.first].second = -1e17;
                    }
                }
            }
        }
        if(bf[n-1].second == -1e17)return -1;
    }
    return -bf[n-1].second; 
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n,m;
    cin >> n >> m;

    
    vector<pair<int,long long int>> *adjBF = new vector<pair<int,long long int>>[n];

    for (int i = 0; i < m; ++i){
        int u,v;
        long long int w;
        cin >> u >> v >> w;
        //Maximize distance , so -w
        addEdge(adjBF,u-1,v-1,-w);
    }

    cout<<solve(adjBF,n); 
}