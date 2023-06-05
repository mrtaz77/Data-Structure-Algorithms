#include <bits/stdc++.h>
using namespace std;

double edgeWeight(vector<pair<int,double>> adj[],int u,int v){
    for(auto x:adj[u]){
        if(x.first==v){
            return x.second;
        }
    }
    return INFINITY;	
}

void rmEdge(vector<pair<int,double>> adj[],int u,int v){
    for(int i=0;i<adj[u].size();i++){
        if(adj[u][i].first == v)adj[u].erase(adj[u].begin()+i);
    }
}

void addEdge(vector<pair<int,double>> adj[],int u,int v,double w){
    if(edgeWeight(adj,u,v) == INFINITY)adj[u].push_back({v,w});
    else{
        rmEdge(adj,u,v);
        adj[u].push_back({v,w});
    }
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

vector<pair<int,int>> BFStraversal(vector<pair<int,double>>adj[],int n){
    vector<pair<int,int>>bfsTree;
    vector<bool>visited(n,false);
    vector<int>parent(n,-1);
    vector<double>dist(n,INFINITY);
    dist[0] = 0;
    queue<int>q;

    for(int i=0;i<n;i++){
        if(!visited[i]){
            q.push(i);
            while(!q.empty()){
                int u = q.front();
                q.pop();
                visited[u] = true;
                for(auto x:adj[u]){
                    if(!visited[x.first]){
                        parent[x.first] = u;
                        dist[x.first] = x.second;
                        q.push(x.first);
                    }
                }
            }
        }
    }

    for(int i=0;i<n;i++){
        if(parent[i] != -1)bfsTree.push_back({parent[i],i});
    }

    return bfsTree;
}

int main(){

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);


    int n,m,start;
    cin>>n>>m;
    vector<pair<int,double>> *adj = new vector<pair<int,double>>[n];
    for(int i=0;i<m;i++){
        int u,v;
        double w;
        cin>>u>>v>>w;
        addEdge(adj,u,v,w);
    }
    print(adj,n);

    cin>>start;

    vector<pair<int,int>> bfsTree = BFStraversal(adj,n);
    
    cout<<"BFS Tree : \n";

    for(auto x:bfsTree){
        cout<<x.first<<" -> "<<x.second<<endl;
    }

    delete[]adj;
}