#include<bits/stdc++.h>
#include"GraphUtil.h"
using namespace std;
vector<vector<long double>> floydWarshall(vector<pair<int,long double>> adj[],int n){
    vector<vector<long double>> dis(n, vector<long double>(n, 1e17));  
    for(int i=0;i<n;i++){
        dis[i][i] = 0;
        for(auto x:adj[i]){
            if(i == x.first){
                if(x.second < 0){
                    dis.clear();
                    return dis;
                }
            }
            else dis[i][x.first] = min(dis[i][x.first],x.second); 
        }
    }

    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(!(dis[i][k] == 1e17 || dis[k][j] == 1e17))dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);
            }
        }
    }
    for(int i=0;i<n;i++)if(dis[i][i] < 0)dis.clear(); 
    return dis;
}

vector<vector<long double>> matProduct(vector<pair<int,long double>> adj[],int n){ 
    vector<vector<long double>> disM(n, vector<long double>(n, 1e17));
    for(int i=0;i<n;i++){
        disM[i][i] = 0;
        for(auto x:adj[i]){
            if(i == x.first){
                if(x.second < 0){
                    disM.clear();
                    return disM;
                }
            }
            else disM[i][x.first] = min(disM[i][x.first],x.second); 
        }
    }

    for(int m=1;m<n-1;m*=2){
        vector<vector<long double>> dis2M = disM;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                for(int k=0;k<n;k++){
                    if(!(dis2M[i][k] == 1e17 || dis2M[k][j] == 1e17))disM[i][j] = min(disM[i][j],dis2M[i][k]+dis2M[k][j]); 
                }
            }
        }
    }
    

    for(int i=0;i<n;i++)if(disM[i][i] < 0)disM.clear(); 
    return disM;
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
                if(disFW[i][j] == 1e17)cout<<"INF ";
                else cout<< disFW[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    cout<<endl;

    cout<<"Matrix Multiplication:"<<endl;
    auto disMat = matProduct(adj,n);
    if(disMat.size() == 0)cout<<"Negative Weight Cycle Present"<<endl;
    else{
        cout<<"Shortest distance matrix"<<endl;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(disMat[i][j] == 1e17)cout<<"INF ";
                else cout<< disMat[i][j]<<" ";
            }
            cout<<endl;
        }
    }
}

