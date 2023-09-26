#include <bits/stdc++.h>
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;

int tripletSum(int a[],int low,int high){
    if(high-low+1 == 3){
        int sum = 0;
        for(int i = low; i <= high; i++)sum += a[i];
        return sum;
    }
    else{
        int mid = (low+high)/2;
        int left = INT_MIN;
        int right = INT_MIN;
        if(mid-low+1 >= 3)left = tripletSum(a,low,mid); 
        if(high-mid >= 3)right = tripletSum(a,mid+1,high);
        int across = max( a[mid-1] + a[mid] + a[mid+1],a[mid] + a[mid+1] + a[mid+2]);
        return max(max(left,right),across);
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int a[n];
        for(int i=0; i<n; i++)cin>>a[i];
        cout<<tripletSum(a,0,n-1)<<endl;
    }
}