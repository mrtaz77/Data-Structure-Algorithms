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

void maxFlow(vector<pair<int,long long>> adj[],int n,int s,int t){
    auto augPath = augmentUtil(adj,s,t);
    vector<pair<int,long long int>> *net = new vector<pair<int,long long int>>[n];


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
            if(edgeWeight(net,v,u)==1e17){
                rmEdge(net,u,v);
                addEdge(net,u,v,prevFlow+bottleNeck);
            }
            else{
                long long netPrev = edgeWeight(net,v,u);
                rmEdge(net,v,u);
                addEdge(net,v,u,netPrev-bottleNeck);
            }
            
            // print(net,n);
        }
        // cout<<"================================\n";
        // print(net,n);
        // cout<<"================================\n";
        maxFlow += bottleNeck;
        augPath = augmentUtil(adj,s,t);
    }
    cout<<maxFlow<<endl;
    // print(net,n);
    // print(adj,n);

    // auto minCut = minCutUtil(adj,n,s);  

    // for(int i=0;i<minCut.size();i++)cout<<minCut[i].first+1<<" "<<minCut[i].second+1<<endl;

    for(int i=0;i<maxFlow;i++){
        auto netAug = augmentUtil(net,s,t); 
        if(netAug.size()){
            long long bottleNeck = 1e17;
            for(int i = 0; i < netAug.size()-1; i++){
                int u = netAug[i];
                int v = netAug[i+1];
                bottleNeck = min(bottleNeck,edgeWeight(net,u,v));
            }
            cout<<netAug.size()<<endl;
            for(int i = 0; i <netAug.size(); i++)cout<<netAug[i]+1<<" ";
            cout<<endl;
            for(int i = 0; i < netAug.size()-1; i++)rmEdge(net,netAug[i],netAug[i+1]);
        }
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n,m;
    cin >> n >> m;

    vector<pair<int,long long int>> *adj = new vector<pair<int,long long int>>[n];

    for(int i = 0; i < m; i++){
        int u,v;
        cin >> u >> v ;
        addEdge(adj,u-1,v-1,1);
    }
    maxFlow(adj,n,0,n-1);
}