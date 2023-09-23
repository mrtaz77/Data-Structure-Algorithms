#include <bits/stdc++.h>
using namespace std;

long long int nPathsSpaceMN(int m,int n){
    long long int a[m][n]; 
    for(int i=0;i<n;i++)a[0][i] = 1;
    for(int i=0;i<m;i++)a[i][0] = 1;

    for(int i=1;i<m;i++){
        for(int j=1;j<n;j++){
            a[i][j] = a[i-1][j] + a[i][j-1];
        }
    }
    return a[m-1][n-1];
}//Time : O(m*n) Space : O(m*n)

long long int nPathsSpaceN(int m,int n){
    long long int a[n] = {1};
    //a[0] = 1;

    for(int i=0;i<m;i++){
        for(int j=1;j<n;j++){
            a[j] += a[j-1];
        }
    }

    return a[n-1];
}//Time : O(m*n) Space : O(n)



int nPathsSpace1(int m, int n)
{
    int path = 1;
    for (int i = n; i < (m + n - 1); i++) {
        path *= i;
        path /= (i - n + 1);
    }
    return path;
}//Time : O(m+n-1) Space : O(1)




int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t;
    cin >> t;
    while(t--){
        int n,m;
        cin >> m >> n;
        cout<<nPathsSpaceMN(m,n)<<endl;
        cout<<nPathsSpaceN(m,n)<<endl;
        cout<<nPathsSpace1(m,n)<<endl;
        cout<<"==========\n";
    }
}