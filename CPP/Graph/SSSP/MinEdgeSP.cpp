#include<bits/stdc++.h>
using namespace std;

void addEdge(vector<pair<int,long double>> adj[],int u,int v,long double w=1.0){adj[u].push_back({v,w});}

void print(vector<pair<int,long double>> adj[],int n){
    for(int i=0;i<n;i++){
        cout<<i<<" -> ";
        for(auto x:adj[i]){
            cout<<x.first<<"("<<x.second<<") ";
        }
        cout<<endl;
    }
}

vector<long long> dijkstra(vector<pair<int,long double>> adj[],int n,int start){
    vector<pair<int,long double>> djk(n,{-1,1e17});
    vector<long long> pathL(n,0);
    priority_queue<pair<long double,int>,vector<pair<long double,int>>,greater<pair<long double,int>>> minHeap;

    djk[start] = {start,0};
    pathL[start] = 0;
    minHeap.push({0,start});

    while(!minHeap.empty()){
        int u = minHeap.top().second;
        long double dis = minHeap.top().first;
        minHeap.pop();

        for(auto x:adj[u]){
            int v = x.first;
            long double weight = x.second;

            if(djk[u].second != 1e17 && (weight + djk[u].second < djk[v].second || (weight + djk[u].second == djk[v].second && pathL[u]+1<pathL[x.first]))){
                djk[v].first = u;
                djk[v].second = weight + djk[u].second;
                pathL[x.first] = pathL[u]+1;
                minHeap.push({djk[v].second,v});
            }
        }
    }
    return pathL;
}

vector<int> pathUtil(vector<pair<int,long double>> sssp,int n,int s,int d){
    vector<int> path;
    int i = d;
    path.push_back(i);
    do{
        path.push_back(sssp[i].first);
        i = sssp[i].first;
    }while(i!=s);
    reverse(path.begin(), path.end());
    return path;
}

int main(){

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n,m,s;
    cin >> n >> m;

    
    vector<pair<int,long double>> *adjDJK = new vector<pair<int,long double>>[n];
    
    for (int i = 0; i < m; ++i){
        int u,v;
        long double w;
        cin >> u >> v >> w;
        addEdge(adjDJK,u,v,w);
    }
    cin>>s;
    print(adjDJK,n);
    cout<<"Dijkstra Algorithm:\n";
    auto djk = dijkstra(adjDJK,n,s);
    for(int i = 0; i < n; ++i)cout<<djk[i]<<" ";
    cout<<endl;
}