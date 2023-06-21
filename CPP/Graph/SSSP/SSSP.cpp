#include<bits/stdc++.h>
#include"GraphUtil.h"
using namespace std;

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

vector<pair<int,double>> dijkstra(vector<pair<int,double>> adj[],int n,int start){
    vector<pair<int,double>> djk(n,{-1,INFINITY});
    priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>> minHeap;


    djk[start].second = 0;
    minHeap.push({0,start});
    

    while(!minHeap.empty()){
        int u = minHeap.top().second;
        double dis = minHeap.top().first;
        minHeap.pop();

        for(auto x:adj[u]){
            int v = x.first;
            double weight = x.second;

            if(weight + djk[u].second < djk[v].second){
                djk[v].first = u;
                djk[v].second = weight + djk[u].second;
                minHeap.push({djk[v].second,v});
            }
        }
    }
    // for(auto x:djk)cout<<x.first<<"("<<x.second<<") ";
    // cout<<endl;
    return djk;
}

vector<int> pathUtil(vector<pair<int,double>> sssp,int n,int s,int d){
    vector<int> path;
    if(s == d){
        path.push_back(d);
        return path;
    }
    int i = d;
    path.push_back(d);
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

    
    vector<pair<int,double>> *adjDJK = new vector<pair<int,double>>[n];
    vector<pair<int,double>> *adjBF = new vector<pair<int,double>>[n];

    for (int i = 0; i < m; ++i){
        int u,v;
        double w;
        cin >> u >> v >> w;
        addEdge(adjDJK,u,v,abs(w));
        addEdge(adjBF,u,v,w);
    }
    cin >> s>>d;
    // print(adjDJK,n);
    cout<<"Bellman Ford Algorithm:\n";
    auto bf = bellFord(adjBF,n,s);
    if(bf.size()==0){
        cout<<"Negative weight cycle present"<<endl;
    }
    else{
        cout<<bf[d].second<<endl;
        vector<int> pathBf = pathUtil(bf,n,s,d);
        for(int i = 0; i < pathBf.size(); ++i){
            cout<<pathBf[i];
            if(i!=pathBf.size()-1)cout<<"->";
        }
        cout<<endl;
    }

    cout<<"Dijkstra Algorithm:\n";
    auto djk = dijkstra(adjDJK,n,s);
    cout<<djk[d].second<<endl;
    vector<int> pathDjk = pathUtil(djk,n,s,d);
    for(int i = 0; i < pathDjk.size(); ++i){
        cout<<pathDjk[i];
        if(i!=pathDjk.size()-1)cout<<"->";
    }
    cout<<endl;
}

// CSES High Score
// CSES Cycle Finding