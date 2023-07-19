#include<bits/stdc++.h>
#include"GraphUtil.h"
using namespace std;

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

vector<int> minCutUtil(vector<pair<int,long long>> adj[],int s,int t){
    vector<int> cut;

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
    for(int i = 0; i < visited.size();i ++){
        if(visited[i])cut.push_back(i);
    }
    return cut;
}


vector<int> certificateOfElimination(vector<pair<int,long long>> adj[],int n,int s,int t){
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
            int cap = edgeWeight(adj,u,v);
            rmEdge(adj,u,v);
            addEdge(adj,u,v,cap-bottleNeck);
            addEdge(adj,v,u,bottleNeck);
        }
        maxFlow += bottleNeck;
        augPath = augmentUtil(adj,s,t);
    }

    auto minCut = minCutUtil(adj,s,t);  

    // cout<<"Min Cut"<<endl;
    // for(int i = 0; i < minCut.size();i++){cout<<minCut[i];if(i!=minCut.size()-1)cout<<" -> ";}
    // cout<<endl;

    vector<int> cert;
    for(int j = 0; j < minCut.size(); j++){
        if(minCut[j] != s && minCut[j] < n)cert.push_back(minCut[j]);
    }

    // cout<<"Certificate"<<endl;
    // for(int i = 0; i < cert.size();i++){cout<<cert[i];if(i!=cert.size()-1)cout<<" -> ";}
    // cout<<endl;

    return cert;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n;
    cin >> n;

    // initializations
    map<int,string> teams;
    vector<long long> w(n,0);
    vector<long long> l(n,0);
    vector<long long> r(n,0);
    vector<vector<long long>> fixture(n,vector<long long>(n,0));
    
    for(int i=0;i<n;i++){
        cin >> teams[i] >> w[i] >> l[i] >> r[i] ;
        for(int j=0;j<n;j++){
            cin >> fixture[i][j];
        }
    }


    // main driver loop
    for(int i=0;i<n;i++){
        bool eliminated = false;
        // maxFlow Graph

        int nodes = 2 + (n-1) + ((n-1)*(n-2))/2;
        vector<pair<int,long long>> *adj = new vector<pair<int,long long>>[nodes];

        // other teams to destination
        for(int j=0;j<n;j++){
            if(j == i)continue;
            int chance = w[i]+r[i]-w[j];
            if(chance >= 0)addEdge(adj,j,nodes-1,chance);
            else{
                eliminated = true;
                cout<<teams[i]<<" is eliminated."<<endl;
                cout<<"They can win at most "<<w[i]<<" + "<<r[i]<<" = "<<w[i]+r[i]<<" games."<<endl;
                cout<<teams[j]<<" has won a total of "<<w[j]<<" games."<<endl;
                cout<<"They play each other 0 times."<<endl;
                cout<<"So on average, each of the teams in this group wins "<<w[j]<<"/1 = "<<w[j]<<" games.\n"<<endl;  
                break;  
            }
        }
        if(eliminated)continue;

        int k = n;
        for(int u=0;u<n-1;u++){
            if(u == i)continue;
            for(int v=u+1;v<n;v++){
                if(v == i)continue;
                // matches to teams
                adj[k].push_back({u,1e17});
                adj[k].push_back({v,1e17});
                // source to teams
                adj[i].push_back({k,fixture[u][v]});
                k++;
            }
        }
        // print(adj,n);

        auto cert = certificateOfElimination(adj,n,i,nodes-1);
        if(cert.size() == 0)cout<<teams[i]<<" is not eliminated.\n"<<endl;
        else {
            eliminated = true;
            cout<<teams[i]<<" is eliminated."<<endl;
            cout<<"They can win at most "<<w[i]<<" + "<<r[i]<<" = "<<w[i]+r[i]<<" games."<<endl;
            if(cert.size() == 1){
                cout<<teams[cert[0]]<<" has won a total of "<<w[cert[0]]<<" games."<<endl;
                cout<<"They play each other 0 times."<<endl;
                cout<<"So on average, each of the teams in this group wins "<<w[cert[0]]<<"/1 = "<<w[cert[0]]<<" games.\n"<<endl;  
            }
            else{
                for(int c=0; c<cert.size(); c++){
                    cout<<teams[cert[c]];
                    if(c==cert.size()-2)cout<<" and ";
                    else if(c!=cert.size()-1)cout<<", ";
                }
                cout<<" have won a total of ";
                long long sum = 0;
                for(int c=0; c<cert.size(); c++)sum+=w[cert[c]];
                cout<<sum<<" games.\n";
                cout<<"They play each other ";
                long long tot_games = 0;
                for(int c1=0; c1<cert.size()-1; c1++){
                    for(int c2=c1+1; c2<cert.size(); c2++){
                        tot_games+=fixture[cert[c1]][cert[c2]];
                    }
                }
                cout<<tot_games<<" times.\n";
                cout<<"So on average, each of the teams wins "<<tot_games+sum<<"/"<<cert.size()<<" = "<<double(tot_games+sum)/double(cert.size())<<" games."<<endl;	
            }
            cout<<endl;
        }
    }
}