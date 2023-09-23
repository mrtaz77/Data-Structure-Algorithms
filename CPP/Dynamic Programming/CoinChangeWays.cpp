#include <bits/stdc++.h>
using namespace std;
int coinWaysOmn(int coins[],int n,int target){
    int dp[n+1][target+1];
    for(int i = 0; i <= n; i++)dp[i][0] = 1;
    for(int i = 1; i <= target; i++)dp[0][i] = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= target; j++){
            if(coins[i-1] > j)dp[i][j] = dp[i-1][j];
            else dp[i][j] = dp[i-1][j] + dp[i][j - coins[i-1]];
        }
    }
    return dp[n][target];
}

int coinWaysOm(int coins[],int n,int target){
    int dp[target+1] = {0};
    dp[0] = 1;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= target; j++){
            if(coins[i-1] <= j){
                dp[j] += dp[j-coins[i-1]]; 
            }
        }
    }
    return dp[target];
}



int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while(t--){
        int n,target;
        cin >> n >> target;
        int coins[n];
        for(int i=0;i<n;i++)cin >> coins[i];
        cout<<coinWaysOmn(coins,n,target)<<endl; 
        cout<<coinWaysOm(coins,n,target)<<endl;
        cout<<"================================================================\n";
    }
}