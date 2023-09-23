#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n,W,i,j;
    cin >> n;
    int value[n];
    int weight[n];
    for(i = 0; i < n; i++)cin >> weight[i] >> value[i];
    cin >> W;

    int cost[n+1][W+1];
    for(i=0;i<=n;i++)cost[i][0] = 0;
    for(i=0;i<=W;i++)cost[0][i] = 0;

    for(i = 1;i<=n;i++){
        for(j=1;j<=W;j++){
            if(weight[i-1]>j)cost[i][j] = cost[i-1][j];
            else cost[i][j] = max(value[i-1] + cost[i-1][j-weight[i-1]],cost[i-1][j]);
        } 
    }

    for(int i = 0; i <= n; i++){
        for(int j = 0; j <=W;j++)cout<<cost[i][j]<<" ";
        cout<<endl;
    }

    cout<<cost[n][W]; 
    cout<<endl;
    

    i = n;
    j = W;

    int soln[n];
    int k = 0;


    while(i > 0 && j > 0){
        if(cost[i-1][j] == cost[i][j])i--;
        else{
            soln[k++] = weight[i-1];
            j -= weight[i-- -1];
        }
    }   

    while(k>0)cout<<soln[--k]<<" ";
}