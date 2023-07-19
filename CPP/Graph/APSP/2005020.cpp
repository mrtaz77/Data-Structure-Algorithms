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
                if(!(dis[i][k].second == 1e17 || dis[k][j].second == 1e17) && (dis[i][j].second > dis[i][k].second + dis[k][j].second)){
                    dis[i][j].second = dis[i][k].second + dis[k][j].second;
                    dis[i][j].first = dis[k][j].first;
                }
            }
        }
    }
    
    for(int i=0;i<n;i++)if(dis[i][i].second < 0)dis.clear(); 
    return dis;
}

void printPathUtil(vector<vector<pair<int,long double>>> apsp,int s,int d){
    if(s == d){
        cout<<s+1;
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
        addEdge(adj,v-1,u-1,w);
    }

    int w1,w2;
    cin >> w1 >> w2;

    auto disFW = floydWarshall(adj,n);


    int u,v;
    cin >> u >> v ;
    while(u != -1 and v != -1){
        if((disFW[w1-1][w2-1].second==1e17)||((disFW[u-1][w1-1].second==1e17 || disFW[w2-1][v-1].second==1e17) &&
        (disFW[u-1][w2-1].second==1e17 || disFW[w1-1][v-1].second==1e17))){
            cout << "No path from " << u << " to " << v <<" through the Wall Street" <<endl;
        }
        else{
            cout<<"Shortest Path Weight: ";
            long double pathw1w2 = disFW[u-1][w1-1].second + disFW[w2-1][v-1].second;
            long double pathw2w1 = disFW[u-1][w2-1].second + disFW[w1-1][v-1].second;
            if(pathw1w2<pathw2w1){
                cout<<disFW[u-1][w1-1].second + disFW[w2-1][v-1].second + disFW[w1-1][w2-1].second;
                cout<<"\nPath: ";
                printPathUtil(disFW,u-1,w1-1);
                cout<<" -> ";
                printPathUtil(disFW,w2-1,v-1);
            }
            else{
                cout<<disFW[u-1][w2-1].second + disFW[w1-1][v-1].second + disFW[w2-1][w1-1].second;
                cout<<"\nPath: ";
                printPathUtil(disFW,u-1,w2-1);
                cout<<" -> ";
                printPathUtil(disFW,w1-1,v-1);
            }
            cout<<"\n";
        }
        cout<<endl;
        cin>>u>>v;
    }
}