#include <iostream>
using namespace std;

int main(){
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while(t--){
        int n,W,i,j;
        cin >> W>>n;
        int value[n];
        int weight[n];
        for(i = 0; i < n; i++)cin >> weight[i] >> value[i];


        int cost[n+1][W+1];
        for(i=0;i<=n;i++)cost[i][0] = 0;
        for(i=0;i<=W;i++)cost[0][i] = 0;

        for(i = 1;i<=n;i++){
            for(j=1;j<=W;j++){
                if(weight[i-1]>j)cost[i][j] = cost[i-1][j];
                else cost[i][j] = max(value[i-1] + cost[i-1][j-weight[i-1]],cost[i-1][j]);
            } 
        }
        cout<<cost[n][W]<<endl; 
    }
}