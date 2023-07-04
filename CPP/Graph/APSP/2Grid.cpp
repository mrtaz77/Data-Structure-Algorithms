#include<bits/stdc++.h>
using namespace std;
long long solve(vector<pair<long long,long long>> &grid,int n){
    vector<vector<long long>> dis(2*n, vector<long long>(2*n, 1e17));
    int i;
    long int mod = 998244353;
    for(i=0;i<n;i++){
        int even = 2*i;
        int odd = 2*i+1;
        dis[even][even] = grid[i].first;
        dis[odd][odd] = grid[i].second;
        dis[even][odd] = dis[odd][even] = (grid[i].first + grid[i].second);
        if(i != n-1){
            dis[even][even+2] = dis[even+2][even] = (grid[i].first + grid[i+1].first);
            dis[odd][even+3] = dis[even+3][odd] = (grid[i].second + grid[i+1].second);
        }
    }
    for(int k=0;k<2*n;k++){
        for(int i=0;i<2*n;i++){
            for(int j=0;j<2*n;j++){
                if(!(dis[i][k] == 1e17 || dis[k][j] == 1e17))dis[i][j] = min(dis[i][j],(dis[i][k]+dis[k][j]-dis[k][k]));
            }
        }
    }
    long long sum = 0;
    for(int i=0;i<2*n;i++){
        for(int j=0;j<2*n;j++){
            if(dis[i][j] != 1e17){
                sum = (sum + dis[i][j])%mod;
            }
        }
    }
    return sum;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    cin >> N;
    vector<pair<long long,long long>> grid(N);
    for(int i=0;i<N;i++){
        cin >> grid[i].first;
    }
    for(int i=0;i<N;i++){
        cin >> grid[i].second;
    }

    cout<<solve(grid,N)<<endl;

}