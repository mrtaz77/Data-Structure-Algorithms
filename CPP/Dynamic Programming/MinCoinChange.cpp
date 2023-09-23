#include <bits/stdc++.h>
using namespace std;

int minCoins(int a[],int n,int target){
    if(target == 0) return 0;
    int dp[target+1];
    dp[0] = 0;
    for(int i = 1; i <= target; i++) dp[i] = INT_MAX;

    for(int i = 1; i <= target; i++){
        //cout<<i<<" : ";
        for(int j = 0;j < n; j++){
            if(a[j] <= i){
                int currCount = dp[i - a[j]];
                if(currCount != INT_MAX && currCount + 1 <dp[i]){
                    dp[i] = currCount + 1;
                }
            }
        }
        cout<<dp[i]<<" ";
    }
    cout<<endl;
    return (dp[target] == INT_MAX) ? -1 : dp[target];
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
        cout<<minCoins(coins,n,target)<<endl; 
    }
}
