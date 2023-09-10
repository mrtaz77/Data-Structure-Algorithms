#define lowerLimit 50
#define upperLimit 200
#include<bits/stdc++.h>
#include"graph.h"
using namespace std;

void floydWarshall(Graph &g){ 
    int n = g.getV();
    
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(!(g.edgeWeight(i,k) == 1e17 || g.edgeWeight(k,j) == 1e17))g.addEdge(i,j,min(g.edgeWeight(i,j), g.edgeWeight(i,k)+g.edgeWeight(k,j)));
            }
        }
    }
}

Graph Create_Random_Graph(int V){
    Graph g(V);
    for(int i=0;i<V-1;i++){
        for(int j=i+1;j<V;j++){
            g.addEdge(i,j,lowerLimit + rand()%(upperLimit-lowerLimit+1));
            g.addEdge(j,i,g.edgeWeight(i,j));
        }
    }
    // cout<<g<<endl;
    floydWarshall(g);
    return g;
}

long double bitmaskDp(int current,long int mask,Graph &G,vector<vector<pair<int,int>>>& dp){
    
    if(mask == (1 << G.getV()) - 1){
        // cout<<current<<" -> "<<0<<endl;
        // cout<<"=="<<endl;
        dp[mask][current].second = 0; 
        return G.edgeWeight(current,0);
    }

    if(dp[mask][current].first != -1){
        // cout<<"++"<<endl;
        return dp[mask][current].first;
    }

    long double ans = MAXG;

    for(int i=0;i < G.getV();i++){
        if(!(mask & (1 << i))){
            long double result = G.edgeWeight(current,i)+bitmaskDp(i,mask|(1<<i),G,dp);
            // if(result < ans)cout<<"--"<<endl;
            if(ans > result){
                ans = result;
                dp[mask][current].second = i;
            }
        }
    }
    // cout<<current<<" "<<endl;
    dp[mask][current].first = ans;
    return ans;
}

vector<int> Exact_TSP(Graph& G){
    vector<vector<pair<int,int>>> dp((1 << G.getV()), vector<pair<int,int>>(G.getV(), {-1,-1}));
    // cout<<"Exact_TSP : "<<endl;
    auto tourLength = bitmaskDp(0,1,G,dp);

    vector<int> tour;
    tour.push_back(0);

    int v = 0;
    int i = 1;
    while(tour.size() <= G.getV()){
        if(dp[i][v].second != -1){
            // cout<<tour.size()<<endl;
            tour.push_back(dp[i][v].second);
            v = dp[i][v].second ;
            i = i | (1 << v);
        }
    }
    
    // for(int i = 0; i <tour.size(); i++)cout<<tour[i]<<" -> ";
    // cout<<endl;

    return tour;
}

Graph primMST(Graph &g,int start){
    int n = g.getV();

    Graph mst(n);
    priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>> minHeap;
    
    vector<double> keys(n,INFINITY);
    vector<int> vis(n,0);
    vector<int> parents(n,-1);

    keys[start] = 0;
    minHeap.push({0,start});

    while(!minHeap.empty()){
        int u = minHeap.top().second;
        minHeap.pop();

        if(vis[u] == 0){

            vector<pair<int,long double>> :: iterator itr;
            vis[u] = 1;

            for(int i = 0; i < n;i++){
                int v = i;
                long double weight = g.edgeWeight(u,v);

                if(vis[v] == 0 && keys[v] > weight){
                    parents[v] = u;
                    keys[v] = weight;
                    minHeap.push({keys[v],v});
                }
            }
        }
    }

    for(int i = 0; i < n; i++){
        if(parents[i] != -1)mst.addEdge(parents[i],i);
    }

    return mst;
}

void DFSUtil(Graph& mst,vector<int> &dfsTree,vector<bool> &visited,vector<int> &parent,int v){
    visited[v] = true;
    for(int i = 0; i < mst.getV() ; i++){
        if(mst.edgeWeight(v,i) != 1e17 && !visited[i]){
            dfsTree.push_back(i);
            parent[i] = v;
            DFSUtil(mst,dfsTree,visited,parent,i);
        }
    }
}

vector<int> DFSTraversal(Graph &mst,int start){
    int n = mst.getV();
    vector<int> dfsTree;
    vector<bool>visited(n,false);
    vector<int>parent(n,-1);
    dfsTree.push_back(start);

    DFSUtil(mst,dfsTree,visited,parent,start);

    dfsTree.push_back(start);

    // for(int i=0;i<n;i++)cout<<parent[i]<<" ";
    // cout<<endl;

    return dfsTree;
}

long double Calculate_Tour_Length(Graph& G,vector<int> &vertices){
    long double tour = 0;
    for(int i=0;i<vertices.size()-1;i++){
        tour += G.edgeWeight(vertices[i],vertices[i+1]);
    }
    return tour;

}

vector<int> Metric_Approximation_TSP(Graph& G){
    Graph mst = primMST(G,0);

    // cout<<mst<<endl;

    auto dfsTree = DFSTraversal(mst,0);

    // for(int i=0;i<dfsTree.size();i++)cout<<dfsTree[i]<<" ";
    // cout<<endl;
    return dfsTree;
    // return 0;
}


