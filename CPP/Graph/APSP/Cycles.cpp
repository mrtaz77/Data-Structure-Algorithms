#include<bits/stdc++.h>
#include"GraphUtil.h"
using namespace std;
vector<vector<pair<int,long double>>> floydWarshall(vector<pair<int,long double>> adj[],int n){
    vector<vector<pair<int,long double>>> dis(n, vector<pair<int,long double>>(n, {-1,1e17}));  
    for(int i=0;i<n;i++){
        dis[i][i].second = 0;
        for(auto x:adj[i]){
            if(x.second < dis[i][x.first].second){
                dis[i][x.first].second = x.second;
                dis[i][x.first].first = i;
            }
        }
    }

    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(!(dis[i][k].second == 1e17 || dis[k][j].second == 1e17) && dis[i][j].second > dis[i][k].second + dis[k][j].second){
                    dis[i][j].second = dis[i][k].second + dis[k][j].second;
                    dis[i][j].first = dis[k][j].first;
                }
            }
        }
    }
    int count = 0;
    vector<bool> vis(n,false);
    for(int i=0;i<n;i++){
        if(dis[i][i].second < 0 && !vis[i]){
            count++;
            cout<<"Negative Cycle "<<count<<" :"<<endl;
            int k = i;
            stack<int> cycle;
            do{
                cycle.push(k);
                k = dis[k][k].first;
                vis[k] = true;
            }while(k != i);
            cycle.push(k);
            while(cycle.size() > 0){
                cout<<cycle.top()+1;
                cycle.pop();
                if(cycle.size() != 0)cout<<" -> ";
            }
            cout<<endl;
        }
    }
    if(count)dis.clear();
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

    cout<<"Floyd Warshall Algorithm:"<<endl;
    auto disFW = floydWarshall(adj,n);
    if(disFW.size() == 0)cout<<"Negative Weight Cycle Present"<<endl;
    else{
        cout<<"Shortest distance matrix"<<endl;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(disFW[i][j].second == 1e17)cout<<"INF ";
                else cout<< disFW[i][j].second<<" ";
            }
            cout<<endl;
        }
        cout<<"\nParent Matrix"<<endl;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(disFW[i][j].first == -1)cout<<"NIL ";
                else cout<< disFW[i][j].first+1<<" ";
            }
            cout<<endl;
        }

        cout<<"\nAll possible paths"<<endl;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                cout<<"("<<i+1<<","<<j+1<<") : ";
                printPathUtil(disFW,i,j);
            }
        }
    }

}

