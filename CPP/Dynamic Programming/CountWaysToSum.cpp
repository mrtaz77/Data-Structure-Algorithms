#include <bits/stdc++.h>
using namespace std;
//Permutations
long long int nWays(int a[],int n,int t){
    long long int sum[t+1] = {0};
    sum[0] = 1;
    for(int i=1;i<=t;i++){
        for(int j=0;j<n;j++){
            if (i >= a[j])sum[i] += sum[i - a[j]];
        }
    }
    return sum[t];
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
        cout<<nWays(a,n,target)<<endl; 
    }
}