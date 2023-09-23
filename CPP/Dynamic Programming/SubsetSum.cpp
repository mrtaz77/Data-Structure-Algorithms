#include <bits/stdc++.h>
using namespace std;

bool subsetSum(int a[],int n,int t){
    bool sum[n+1][t+1];
    for(int i=0;i<=n;i++)sum[i][0] = true;
    for(int i=1;i<=t;i++)sum[0][i] = false;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=t;j++){
            if(j < a[i-1])sum[i][j] = sum[i-1][j];
            else{
                sum[i][j] = sum[i-1][j] || sum[i-1][j-a[i-1]];
            }
        }
    }

    for(int i=0;i<=n;i++){
        for(int j=0;j<=t;j++)cout<<boolalpha<<sum[i][j]<<" ";
        cout<<endl;
    }

    
    if(sum[n][t]){
        int p = n;
        int q = t;
        while(p >= 0 && q >= 0){
            if(sum[p][q] == sum[p-1][q])p--;
            else{
                if(sum[p][q] == sum[p-1][q-a[p-1]]){
                    cout<<a[p-1]<<" ";
                    q -= a[p-1];
                }
                p--;
            }
        }
        cout<<endl;
    }
    return sum[n][t];
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while(t--){
        int n,target;
        cin >> n >> target;
        int a[n];
        for(int i=0;i<n;i++)cin >> a[i];
        cout<<boolalpha<<subsetSum(a,n,target)<<endl; 
    }
}