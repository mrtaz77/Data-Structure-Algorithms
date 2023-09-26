#include<bits/stdc++.h>
using namespace std;

int countMerge(string a,int l,int h){
    int mid = (l+h)/2;
    int p1 = mid,p2 =mid+1;
    

    if(a[mid] != a[mid+1] + 1)return 0;
    while(a[p1] + 1 == a[p1-1] && p1 > l)p1--;
    int left = mid - p1+1;
    
    while(a[p2] == a[p2+1] + 1 && p2 < h)p2++;
    int right = p2-mid;

    return left*right;
}

int countInvDQ(string a,int l,int h){
    if(h == l)return 0;
    else if(h == l+1){
        if(a[l] == a[h] + 1)return 1;
        return 0;
    }
    else{
        int mid = (l+h)/2;
        int left = countInvDQ(a,l,mid);
        int right = countInvDQ(a,mid+1,h);
        int across = countMerge(a,l,h);
        return left+right+across;
    }
}

int countInv(string s){
    int i = 0,j = 0,sum = 0;
    while(j<s.length()-1){
        if(s[j] != s[j+1]+1){
            int n = j-i+1;
            i = j+1;
            sum += n*(n-1)/2;
        }
        j++;
    }
    if(s[j] == s[j-1]-1){
        int n = j-i+1;
        sum += n*(n-1)/2;
    }
    return sum;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        cout<<countInvDQ(s,0,s.length()-1)<<" : ";
        cout<<countInv(s)<<endl;
    }
}
