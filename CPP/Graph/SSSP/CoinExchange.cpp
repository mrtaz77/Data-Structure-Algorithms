#include<bits/stdc++.h>
using namespace std;
void addEdge(vector<pair<int,long double>> adj[],int u,int v,long double w=1.0){adj[u].push_back({v,w});}
vector<pair<int,long double>> bellFord(vector<pair<int,long double>> adj[],int n,int start){
    vector<pair<int,long double>> bf(n,{-1,1e17});
    bf[start] = {start,0};
    int k = -1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(auto x:adj[j]){
                if(bf[j].second != 1e17 && bf[j].second + x.second < bf[x.first].second){
                    bf[x.first].second = bf[j].second + x.second;
                    bf[x.first].first = j;
                    if(i == n-1)k = x.first;
                }
            }
        }
    }
    //if cycle present and reachable from source,checking 
    //whether a path exists between src and des including the neg cycle
    //if exists then the following iterations makes the distances -INF
    if(k != -1){
        bf[k].second = -1e17;
        for(int i=0;i<n-1;i++){
            for(int j=0;j<n;j++){
                for(auto x:adj[j]){
                    if(bf[j].second != 1e17 && bf[j].second + x.second < bf[x.first].second){
                        bf[x.first].second = -1e17;
                        bf[x.first].first = j;
                    }
                }
            }
        }
    }
    return bf;
}

bool checkCycle(vector<pair<int,long double>> adj[],int n){
    vector<pair<int,long double>> bf(n,{-1,0});
    int k = -1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(auto x:adj[j]){
                if(bf[j].second + x.second < bf[x.first].second){
                    bf[x.first].second = bf[j].second + x.second;
                    bf[x.first].first = j;
                    if(i == n-1)k = x.first;
                }
            }
        }
    }
    if(k != -1)return true;
    return false;
}


vector<int> pathUtil(vector<pair<int,long double>> sssp,int n,int s,int d){
    vector<int> path;
    int i = d;
    path.push_back(i);
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

    vector<pair<int,long double>> *adjBF = new vector<pair<int,long double>>[n];

    for (int i = 0; i < m; ++i){
        int u,v;
        long double w;
        cin >> u >> v >> w;
        addEdge(adjBF,u,v,-log(w));
    }
    cin >> s>>d;
    //print(adjDJK,n);
    
    if(checkCycle(adjBF,n)){
        cout<<"There is an anomaly"<<endl;
    }
    else{
        cout<<"There are no anomalies"<<endl<<"Best exchange rate: ";
        auto bf = bellFord(adjBF,n,s);
        if(bf[d].second == 1e17)cout<<"0\n";
        else{
            cout<<exp(-bf[d].second)<<endl;
            vector<int> pathBf = pathUtil(bf,n,s,d);
            for(int i = 0; i < pathBf.size(); ++i){
                cout<<pathBf[i];
                if(i!=pathBf.size()-1)cout<<"->";
            }
            cout<<endl;
        }
    }
}