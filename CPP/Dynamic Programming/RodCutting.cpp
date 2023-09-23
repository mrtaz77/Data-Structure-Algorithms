#include <bits/stdc++.h>
using namespace std;

int rodCutMax(int a[],int n){
    int dp[n+1] = {0};
    int cuts[n+1] = {0};
    for(int len = 1;len <= n;len++){
        for(int i = 1;i <= len;i++){
            int temp = a[i-1] + dp[len-i];
            if(temp>dp[len]){
                dp[len] = temp;
                cuts[len] = i;
            }
        }
    }
    int i = n;
    while(i > 0){
        cout<<cuts[i]<<" ";
        i -= cuts[i];
    }
    cout<<endl;
    return dp[n];
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while(t--){
        int n,target;
        cin >> n;
        int a[n];
        for(int i=0;i<n;i++)cin >> a[i];
        cout<<rodCutMax(a,n)<<endl;
    }
}