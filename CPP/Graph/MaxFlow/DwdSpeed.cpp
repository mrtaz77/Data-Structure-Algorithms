#include<bits/stdc++.h>
using namespace std;
long long edgeWeight(vector<pair<int,long long>> adj[],int u,int v){
    long long weight = 1e17;
    for(auto x:adj[u]){
        if(x.first==v && x.second < weight){
            weight = x.second;
        }
    }
    return weight;	
}

void rmEdge(vector<pair<int,long long>> adj[],int u,int v){
    for(int i=0;i<adj[u].size();i++){
        if(adj[u][i].first == v)adj[u].erase(adj[u].begin()+i);
    }
}

void addEdge(vector<pair<int,long long>> adj[],int u,int v,long long w=1.0){adj[u].push_back({v,w});}

void print(vector<pair<int,long long>> adj[],int n){
    for(int i=0;i<n;i++){
        cout<<i<<" -> ";
        for(auto x:adj[i]){
            cout<<x.first<<"("<<x.second<<") ";
        }
        cout<<endl;
    }
}
vector<int> augmentUtil(vector<pair<int,long long>> adj[],int s,int t){
    vector<int> path;

    vector<bool>visited(t+1,false);
    vector<int>parent(t+1,-1);
    
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(auto x:adj[v]){
            if(!(visited[x.first] || edgeWeight(adj,v,x.first) <= 0)){
                q.push(x.first);
                parent[x.first] = v;
                visited[x.first] = true;
            }
        }
    }
    if(visited[t]){
        int pre = t;
        do{
            path.push_back(pre);
            pre = parent[pre];
            if(pre == s)path.push_back(pre);
        }while(pre != s);
        reverse(path.begin(),path.end());
    }
    // cout<<"Augmented paths"<<endl;
    // for(int i = 0; i < path.size();i++){cout<<path[i];if(i!=path.size()-1)cout<<" -> ";}
    // cout<<endl;
    return path;
}

vector<pair<int,int>> minCutUtil(vector<pair<int,long long>>adj[],int n,int start){
    vector<pair<int,int>> minCut;
    vector<int>bfsVert;
    vector<bool>visited(n,false);
    vector<int>parent(n,-1);
    vector<double>dist(n,INFINITY);
    dist[start] = 0;
    queue<int>q;
    q.push(start);
    visited[start] = true;
    bfsVert.push_back(start);
    while(!q.empty()){
        int v = q.front();
        q.pop();
        for(auto x:adj[v]){
            if(!(visited[x.first] || edgeWeight(adj,v,x.first) <= 0)){
                q.push(x.first);
                parent[x.first] = v;
                dist[x.first] = dist[v] + edgeWeight(adj,v,x.first);
                bfsVert.push_back(x.first);
                visited[x.first] = true;
            }
        }
    }
    // for(int i = 0; i < bfsVert.size();i++)cout<<bfsVert[i]<<" ";
    // cout<<endl;
    for(int i=0;i<bfsVert.size();i++){
        // cout<<bfsVert[i]<<" : ";
        for(auto x:adj[bfsVert[i]]){
            // cout<<x.first<<" ";
            if(!visited[x.first] && edgeWeight(adj,bfsVert[i],x.first)==0){
                minCut.push_back({bfsVert[i],x.first});
            }
        }
        // cout<<endl;
    }
    return minCut;
}

void maxFlow(vector<pair<int,long long>> adj[],int n,int s,int t){
    auto augPath = augmentUtil(adj,s,t);

    long long maxFlow = 0;
    while(augPath.size()){
        long long bottleNeck = 1e17;
        for(int i = 0; i < augPath.size()-1; i++){
            int u = augPath[i];
            int v = augPath[i+1];
            bottleNeck = min(bottleNeck,edgeWeight(adj,u,v));
        }

        
        for(int i = 0; i < augPath.size()-1; i++){
            int u = augPath[i];
            int v = augPath[i+1];
            long long cap = edgeWeight(adj,u,v);
            long long prevFlow = edgeWeight(adj,v,u);
            rmEdge(adj,u,v);
            addEdge(adj,u,v,cap-bottleNeck);
            rmEdge(adj,v,u);
            if(prevFlow == 1e17)prevFlow = 0;
            addEdge(adj,v,u,prevFlow+bottleNeck);
        }
        maxFlow += bottleNeck;
        augPath = augmentUtil(adj,s,t);
    }
    cout<<maxFlow<<endl;
    // print(adj,n);

    auto minCut = minCutUtil(adj,n,s);  

    // for(int i=0;i<minCut.size();i++)cout<<minCut[i].first+1<<" "<<minCut[i].second+1<<endl;
}

int main(){
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    int n,m;
    cin >> n >> m;
    
    vector<pair<int,long long int>> *adj = new vector<pair<int,long long int>>[n];

    for (int i = 0; i < m; ++i){
        int u,v;
        long long int w;
        cin >> u >> v>>w;
        if(edgeWeight(adj,u-1,v-1)==1e17)addEdge(adj,u-1,v-1,w);
        else{
            long long int prev = edgeWeight(adj,u-1,v-1);
            rmEdge(adj,u-1,v-1);
            addEdge(adj,u-1,v-1,w+prev);
        }
        // addEdge(adj,v-1,u-1,1);
        // if(edgeWeight(adj,v,u)==1e17)addEdge(adj,v,u,0);
    }
    // print(adj,n);
    maxFlow(adj,n,0,n-1);
}
