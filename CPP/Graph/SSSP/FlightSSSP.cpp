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


vector<pair<int,long double>> genDijkstra(vector<pair<int,long double>> adj[],vector<long double>cost,int n,int start){
    vector<pair<int,long double>> djk(n,{-1,1e17});
    priority_queue<pair<long double,int>,vector<pair<long double,int>>,greater<pair<long double,int>>> minHeap;

    djk[start] = {start,0};
    minHeap.push({0,start});

    while(!minHeap.empty()){
        int u = minHeap.top().second;
        long double dis = minHeap.top().first;
        minHeap.pop();

        for(auto x:adj[u]){
            int v = x.first;
            long double weight = x.second;

            if(djk[u].second != 1e17 && weight + djk[u].second + cost[x.first] < djk[v].second){
                djk[v].first = u;
                djk[v].second = weight + djk[u].second + cost[x.first];
                minHeap.push({djk[v].second,v});
            }
        }
    }
    return djk;
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

    int n,m;
    string s,d;
    cin >> n >> m;
    vector<pair<int,long double>> *adjDJK = new vector<pair<int,long double>>[n];
    vector<long double> cost(n);
    vector<string> ports(n);
    for(int i=0;i<n;i++){
        cin>>ports[i]>>cost[i];
    }
    

    for (int i = 0; i < m; ++i){
        string u,v;
        long double w;
        cin >> u >> v >> w;
        int j,k;
        for(j = 0; j < n && ports[j] != u; j++);
        for(k = 0; k < n && ports[k] != v; k++);
        addEdge(adjDJK,j,k,w);
        addEdge(adjDJK,k,j,w);
    }
    cin>>s>>d;
    int start,des;
    for(start = 0; start < n && ports[start] != s; start++);
    for(des = 0; des < n && ports[des] != d; des++);
    // print(adjDJK,n);

    
    auto djk = genDijkstra(adjDJK,cost,n,start);
    if(djk[des].second == 1e17)cout<<"INF\n";
    else{
        cout<<djk[des].second<<endl;
        vector<int> pathDJK = pathUtil(djk,n,start,des);
        for(int i = 0; i < pathDJK.size(); ++i){
            cout<<ports[pathDJK[i]];
            if(i!=pathDJK.size()-1)cout<<"->";
        }
        cout<<endl;
    }
}