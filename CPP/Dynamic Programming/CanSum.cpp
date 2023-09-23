#include <bits/stdc++.h>
using namespace std;

bool canSum(int a[],int n,int t,vector<pair<int,bool>> &memo){
    for(int i=0;i<memo.size();i++)if(memo[i].first == t)return memo[i].second;
    if(t == 0)return true; 
    else if(t < 0)return false;
    else{
        for(int i = 0; i < n; i++){
            if(canSum(a,n,t-a[i],memo)){
                pair<int,bool> success(t,true);
                memo.push_back(success);
                return true; 
            }
        }
    }
    pair<int,bool> failure(t,false);
    memo.push_back(failure);
    return false;
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
        vector<pair<int,bool>> memo;
        cout<<boolalpha<<canSum(a,n,target,memo)<<endl; 
        //cout<<endl;
    }
}