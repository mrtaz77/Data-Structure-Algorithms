#include <bits/stdc++.h>
using namespace std;
int edit(string s1,string s2){
    int a[s1.size()+1][s2.size()+1];

    for(int i = 0; i <= s1.size(); i++){
        for(int j = 0; j <= s2.size(); j++){
            if(i == 0)a[i][j] = 2*j;
            else if(j == 0)a[i][j] = 2*i;
            else if(s1[i-1] == s2[j-1])a[i][j] = a[i-1][j-1];
            else a[i][j] = min(1+a[i-1][j-1],min(2+a[i-1][j],2+a[i][j-1]));
            cout << a[i][j] <<" ";
        }
        cout<<endl;
    }
    return a[s1.size()][s2.size()];
}//Space O(len(s1)*len(s2))

int editOm(string s1,string s2){
    int a[2][s1.size()+1];

    for(int i = 0;i<=s1.size();i++)a[0][i] = 2*i;

    for(int i = 1;i<=s2.size();i++){
        for(int j = 0;j<=s1.size();j++){
            if(j == 0)a[i%2][j] = 2*i;
            else if(s1[j-1] == s2[i-1])a[i%2][j] = a[(i-1)%2][j-1];
            else{
                a[i%2][j] = min(min(1+a[(i-1)%2][j-1],2+a[(i-1)%2][j]),2+a[i%2][j-1]);
            }
        }
    }
    return a[s2.size()%2][s1.size()];
}//Space O(len(s1)*2)

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while(t--){
        string s1;
        string s2;
        cin >> s1 >> s2;
        cout<<edit(s2,s1)<<endl;
        cout<<editOm(s1,s2)<<endl;
        cout<<"================================================================\n";
    }
}