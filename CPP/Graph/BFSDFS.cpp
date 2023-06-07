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

vector<pair<int,int>> BFStraversal(vector<pair<int,double>>adj[],int n,int start){
    vector<pair<int,int>>bfsTree;
    vector<bool>visited(n,false);
    vector<int>parent(n,-1);
    vector<double>dist(n,INFINITY);
    dist[start] = 0;
    queue<int>q;
    q.push(start);
    visited[start] = true;
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(auto x:adj[v]){
            if(!visited[x.first]){
                q.push(x.first);
                parent[x.first] = v;
                dist[x.first] = dist[v] + edgeWeight(adj,v,x.first);
                bfsTree.push_back({v,x.first});
                visited[x.first] = true;
            }
        }
    }
    // for(int i=0;i<n;i++)cout<<parent[i]<<" ";
    // cout<<endl;
    // for(int i=0;i<n;i++)cout<<dist[i]<<" ";
    // cout<<endl;

    return bfsTree;
}

vector<pair<int,int>> BFSAll(vector<pair<int,double>>adj[],int n){
    vector<pair<int,int>>bfsTree;
    vector<bool>visited(n,false);
    vector<int>parent(n,-1);
    vector<double>dist(n,INFINITY);
    queue<int>q;

    for(int i=0;i<n;i++){
        if(!visited[i]){
            dist[i] = 0;
            q.push(i);
            visited[i] = true;
            while(!q.empty()){
                int v = q.front();
                q.pop();
                for(auto x:adj[v]){
                    if(!visited[x.first]){
                        q.push(x.first);
                        parent[x.first] = v;
                        dist[x.first] = dist[v] + edgeWeight(adj,v,x.first);
                        bfsTree.push_back({v,x.first});
                        visited[x.first] = true;
                    }
                }
            }
        }
    }


    
    // for(int i=0;i<n;i++)cout<<parent[i]<<" ";
    // cout<<endl;
    // for(int i=0;i<n;i++)cout<<dist[i]<<" ";
    // cout<<endl;

    return bfsTree;
}

void DFSHelper(vector<pair<int,double>> adj[],vector<pair<int,int>> &dfsTree,vector<bool> &visited,vector<int> &parent,int v){
    visited[v] = true;
    for(auto x : adj[v]){
        if(!visited[x.first]){
            dfsTree.push_back({v,x.first});
            parent[x.first] = v;
            DFSHelper(adj,dfsTree,visited,parent,x.first);
        }
    }
}

vector<pair<int,int>> DFSTraversal(vector<pair<int,double>> adj[],int n,int start){
    vector<pair<int,int>> dfsTree;
    vector<bool>visited(n,false);
    vector<int>parent(n,-1);

    DFSHelper(adj,dfsTree,visited,parent,start);

    // for(int i=0;i<n;i++)cout<<parent[i]<<" ";
    // cout<<endl;

    return dfsTree;
}

vector<pair<int,int>> DFSAll(vector<pair<int,double>> adj[],int n){
    vector<pair<int,int>> dfsTree;
    vector<bool>visited(n,false);
    vector<int>parent(n,-1);

    for(int i=0;i<n;i++){
        if(!visited[i])DFSHelper(adj,dfsTree,visited,parent,i);
    }

    // for(int i=0;i<n;i++)cout<<parent[i]<<" ";
    // cout<<endl;

    return dfsTree;
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

    vector<pair<int,int>> bfsTree = BFStraversal(adj,n,start);
    
    cout<<"BFS Tree : \n";

    for(int i=0;i<bfsTree.size();i++){
        int v = bfsTree[i].first;
        cout<<v<<" -> ";
        while(bfsTree[i].first==v){
            cout<<bfsTree[i].second;
            i = i+1;
            if(bfsTree[i].first == v)cout<<",";
        }
        i--;
        cout<<endl;
    }

    vector<pair<int,int>> bfsAll = BFSAll(adj,n);
    

    cout<<"BFS all :\n";

    for(int i=0;i<bfsAll.size();i++){
        int v = bfsAll[i].first;
        cout<<v<<" -> ";
        while(bfsAll[i].first==v){
            cout<<bfsAll[i].second;
            i = i+1;
            if(bfsAll[i].first == v)cout<<",";
        }
        i--;
        cout<<endl;
    }

    vector<pair<int,int>> dfsTree = DFSTraversal(adj,n,start);
    
    cout<<"DFS Tree : \n";

    for(int i=0;i<dfsTree.size();i++){
        int v = dfsTree[i].first;
        cout<<v<<" -> ";
        while(dfsTree[i].first==v){
            cout<<dfsTree[i].second;
            i = i+1;
            if(dfsTree[i].first == v)cout<<",";
        }
        i--;
        cout<<endl;
    }

    vector<pair<int,int>> dfsAll = DFSAll(adj,n);
    

    cout<<"DFS all :\n";

    for(int i=0;i<dfsAll.size();i++){
        int v = dfsAll[i].first;
        cout<<v<<" -> ";
        while(dfsAll[i].first==v){
            cout<<dfsAll[i].second;
            i = i+1;
            if(dfsAll[i].first == v)cout<<",";
        }
        i--;
        cout<<endl;
    }

    delete[]adj;
}