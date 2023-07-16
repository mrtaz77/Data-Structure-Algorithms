#include<bits/stdc++.h>
#include"GraphUtil.h"
using namespace std;
vector<pair<int,long double>> dijkstra(vector<pair<int,long double>> adj[],int n,int start){
    vector<pair<int,long double>> djk(n,{-1,1e17});
    priority_queue<pair<long double,int>,vector<pair<long double,int>>,greater<pair<long double,int>>> minHeap;

    djk[start] = {-1,0};
    minHeap.push({0,start});

    while(!minHeap.empty()){
        int u = minHeap.top().second;
        long double dis = minHeap.top().first;
        minHeap.pop();

        for(auto x:adj[u]){
            int v = x.first;
            long double weight = x.second;

            if(djk[u].second != 1e17 && weight + djk[u].second < djk[v].second){
                djk[v].first = u;
                djk[v].second = weight + djk[u].second;
                minHeap.push({djk[v].second,v});
            }
        }
    }
    return djk;
}

vector<vector<pair<int,long double>>> johnson(vector<pair<int,long double>> adj[],int n){
    vector<vector<pair<int,long double>>> dis(n, vector<pair<int,long double>>(n, {-1,1e17}));  
    vector<long double> bf(n,{0});
    vector<pair<int,long double>> *copyG = new vector<pair<int,long double>>[n];
    int k = -1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(auto x:adj[j]){
                if(bf[j] + x.second < bf[x.first]){
                    bf[x.first] = bf[j] + x.second;
                    if(i == n-1)k = x.first;
                }
            }
        }
    }
    if(k != -1){
        dis.clear();
        return dis;
    }

    // reweighting edges
    for(int i=0;i<n;i++){
        for(auto x:adj[i]){
            addEdge(copyG,i,x.first,x.second + bf[i]-bf[x.first]);
        }
    }

    for(int i=0;i<n;i++){
        auto djk = dijkstra(copyG,n,i);
        for(int j=0;j<n;j++){
            if(djk[j].second != 1e17){
                dis[i][j].second = djk[j].second+bf[j]-bf[i];
                dis[i][j].first = djk[j].first;
            }
        }
    }
    return dis;
}

void printPathUtil(vector<vector<pair<int,long double>>> apsp,int s,int d){
    if(s == d){
        cout<<s+1<<" -> "<<d+1<<endl;
    }
    else if(apsp[s][d].first == -1)cout<<"No path exists.\n";
    else{
        stack<int> path;
        path.push(d);
        int parent = apsp[s][d].first;
        do{
            path.push(parent);
            parent = apsp[s][parent].first;

        }while(parent != -1);
        while(path.size() > 0){
            cout<<path.top()+1;
            path.pop();
            if(path.size() > 0)cout<<" -> ";
        }

        cout<<endl;
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n,m;
    cin >> n >> m;
    
    vector<pair<int,long double>> *adj = new vector<pair<int,long double>>[n];

    for (int i = 0; i < m; ++i){
        int u,v;
        long double w;
        cin >> u >> v >> w;
        addEdge(adj,u-1,v-1,w);
    }

    cout<<"Johnson's Algorithm:"<<endl;
    auto disjs = johnson(adj,n);
    if(disjs.size() == 0)cout<<"Negative Weight Cycle Present"<<endl;
    else{
        cout<<"Shortest distance matrix"<<endl;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(disjs[i][j].second == 1e17)cout<<"INF ";
                else cout<< disjs[i][j].second<<" ";
            }
            cout<<endl;
        }
        cout<<"\nParent Matrix"<<endl;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(disjs[i][j].first == -1)cout<<"NIL ";
                else cout<< disjs[i][j].first+1<<" ";
            }
            cout<<endl;
        }

        cout<<"\nAll possible paths"<<endl;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                cout<<"("<<i+1<<","<<j+1<<") : ";
                printPathUtil(disjs,i,j);
            }
        }
    }
}