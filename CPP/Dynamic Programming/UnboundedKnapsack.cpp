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

    int dp[W+1];
    for(i=0;i<=W;i++)dp[i] = 0;

    for(i = 1;i<=W;i++){
        for(j=0;j<n;j++){
            if(weight[j]<=i)dp[i] = max(dp[i],value[j]+dp[i-weight[j]]);
            cout<<dp[i]<<" ";
        }
        cout<<endl;
    }

    cout<<dp[W]; 
    cout<<endl;
}