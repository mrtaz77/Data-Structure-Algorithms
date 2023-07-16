#include<bits/stdc++.h>
#include"GraphUtil.h"
using namespace std;

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

    int n,m,s;
    cin >> n >> m;

    vector<pair<int,long long>> *adjDJK = new vector<pair<int,long long>>[n];
    vector<pair<int,long long>> *transpose = new vector<pair<int,long long>>[n];
    

    for (int i = 0; i < m; ++i){
        int u,v;
        long long w;
        cin >> u >> v >> w;
        addEdge(adjDJK,u,v,w);
        addEdge(transpose,v,u,w);
    }
    cin>>s;

    auto djkSSSP = dijkstra(adjDJK,n,s);
    auto transSSSP = dijkstra(transpose,n,s);
    long long minTime = 1e17;
    int minV = -1;

    for(int i = 0; i < n; ++i){
        if(i != s){
            if(djkSSSP[i].second + transSSSP[i].second < minTime){
                minTime = djkSSSP[i].second + transSSSP[i].second;
                minV = i;
            }
        }
    }

    cout<<"Minimum total time: "<<minTime<<endl<<endl;

    cout<<"Paths:"<<endl;
    vector<int> pathDjk = pathUtil(djkSSSP,n,s,minV);
    for(int i = 0; i < pathDjk.size(); ++i){
        cout<<pathDjk[i];
        if(i!=pathDjk.size()-1)cout<<"->";
    }
    cout<<" (time: "<<djkSSSP[minV].second<<")"<<endl;
    pathDjk = pathUtil(transSSSP,n,s,minV);
    reverse(pathDjk.begin(),pathDjk.end());
    for(int i = 0; i < pathDjk.size(); ++i){
        cout<<pathDjk[i];
        if(i!=pathDjk.size()-1)cout<<"->";
    }
    cout<<" (time: "<<transSSSP[minV].second<<")"<<endl;
}