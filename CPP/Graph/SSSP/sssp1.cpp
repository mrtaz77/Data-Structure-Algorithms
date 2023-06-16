#include<bits/stdc++.h>
using namespace std;

void addEdge(vector<pair<int,double>> adj[],int u,int v,double w=1.0){adj[u].push_back({v,w});}

vector<pair<int,double>>bellFord(vector<pair<int,double>> adj[],int n,int start){
    vector<pair<int,double>> bf(n,{-1,INFINITY});
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


void print(vector<pair<int,double>> adj[],int n){
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
    vector<pair<int,double>> *adjBF = new vector<pair<int,double>>[n];
    for (int i = 0; i < m; ++i){
        int u,v;
        double w;
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
            if(bf[i].second == INFINITY) cout<<"INF"<<endl;
            else cout<<bf[i].second<<endl;
        }
    }
}