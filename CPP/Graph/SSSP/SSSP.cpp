#include<bits/stdc++.h>
#include"GraphUtil.h"
using namespace std;

vector<pair<int,long long>> bellFord(vector<pair<int,long long>> adj[],int n,int start){
    vector<pair<int,long long>> bf(n,{-1,1e17});
    bf[start] = {start,0};
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
                        bf[x.first].first = j;
                    }
                }
            }
        }
    }
    return bf;
}

vector<pair<int,long long>> dijkstra(vector<pair<int,long long>> adj[],int n,int start){
    vector<pair<int,long long>> djk(n,{-1,1e17});
    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> minHeap;

    djk[start] = {start,0};
    minHeap.push({0,start});

    while(!minHeap.empty()){
        int u = minHeap.top().second;
        long long dis = minHeap.top().first;
        minHeap.pop();

        for(auto x:adj[u]){
            int v = x.first;
            long long weight = x.second;

            if(djk[u].second != 1e17 && weight + djk[u].second < djk[v].second){
                djk[v].first = u;
                djk[v].second = weight + djk[u].second;
                minHeap.push({djk[v].second,v});
            }
        }
    }
    return djk;
}

vector<int> pathUtil(vector<pair<int,long long>> sssp,int n,int s,int d){
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

    int n,m,s,d;
    cin >> n >> m;

    
    vector<pair<int,long long>> *adjDJK = new vector<pair<int,long long>>[n];
    vector<pair<int,long long>> *adjBF = new vector<pair<int,long long>>[n];

    for (int i = 0; i < m; ++i){
        int u,v;
        long long w;
        cin >> u >> v >> w;
        addEdge(adjDJK,u,v,abs(w));
        addEdge(adjBF,u,v,w);
    }
    cin >> s>>d;
    //print(adjDJK,n);
    cout<<"Bellman Ford Algorithm:\n";
    auto bf = bellFord(adjBF,n,s);
    if(bf[d].second == -1e17){
        cout<<"Negative weight cycle present"<<endl;
    }
    else{
        if(bf[d].second == 1e17)cout<<"INF\n";
        else{
            cout<<bf[d].second<<endl;
            vector<int> pathBf = pathUtil(bf,n,s,d);
            for(int i = 0; i < pathBf.size(); ++i){
                cout<<pathBf[i];
                if(i!=pathBf.size()-1)cout<<"->";
            }
            cout<<endl;
        }
    }

    cout<<"Dijkstra Algorithm:\n";
    auto djk = dijkstra(adjDJK,n,s);
    if(djk[d].second == 1e17)cout<<"INF\n";
    else{
        cout<<djk[d].second<<endl;
        vector<int> pathDjk = pathUtil(bf,n,s,d);
        for(int i = 0; i < pathDjk.size(); ++i){
            cout<<pathDjk[i];
            if(i!=pathDjk.size()-1)cout<<"->";
        }
        cout<<endl;
    }
}

// CSES High Score
