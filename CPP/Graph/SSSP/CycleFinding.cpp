//CSES Cycle Finding
//Negative cycle detection over the entire graph
//Trick : do bellford with start distance 0
//equivalent of using an imaginary node at 0 distance from every node as starting point node 
#include<bits/stdc++.h>
using namespace std;
void addEdge(vector<pair<int,long double>> adj[],int u,int v,long double w=1.0){adj[u].push_back({v,w});}

void solve(vector<pair<int,long double>> adj[],int n){
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
        cout<<"NO\n";
    }
    else{
        cout<<"YES\n";
        vector<int> cycle;
        for(int i=0;i<n;i++)k = bf[k].first;
        int v = k;
        cycle.push_back(v);
        do{
            k = bf[k].first;
            cycle.push_back(k);
        }while(k != v);
        for(int i=0;i<cycle.size();i++)cout<<cycle[cycle.size()-i-1]+1<<" ";
    }
}


int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n,m;
    cin >> n >> m;

    
    vector<pair<int,long double>> *adjBF = new vector<pair<int,long double>>[n];

    for (int i = 0; i < m; ++i){
        int u,v;
        long double w;
        cin >> u >> v >> w;
        addEdge(adjBF,u-1,v-1,w);
    }

    solve(adjBF,n); 
}