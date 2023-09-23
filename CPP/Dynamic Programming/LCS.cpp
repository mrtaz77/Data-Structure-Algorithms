#include <bits/stdc++.h>
using namespace std;

int lcs(string s1,string s2){
    int a[s1.size()+1][s2.size()+1];
    int D[s1.size()+1][s2.size()+1];
    for(int i=0;i < s1.size()+1;i++)a[i][0] = 0;
    for(int i=0;i < s2.size()+1;i++)a[0][i] = 0;

    for(int i=1;i <= s1.size();i++){
        for(int j=1;j <= s2.size();j++){
            if(s1[i-1] == s2[j-1]){
                a[i][j] = 1 + a[i-1][j-1];
                D[i][j] = 1;
            }
            else{
                if(a[i-1][j] > a[i][j-1]){
                    a[i][j] = a[i-1][j];
                    D[i][j] = 2;
                }
                else{
                    a[i][j] = a[i][j-1];
                    D[i][j] = 3;
                }
            }
        }
    }

    int p = s1.size();
    int q = s2.size();
    string ans;
    while(p > 0 && q > 0){
        if(D[p][q] == 1){
            ans.push_back(s1[p-1]);
            p--;
            q--;
        }
        else if(D[p][q] == 2){
            p--;
        }
        else q--;
    }
    reverse(ans.begin(),ans.end());
    cout<<ans<<endl;
    return a[s1.size()][s2.size()];
}


int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while(t--){
        string s1;
        string s2;
        cin >> s1 >> s2;
        cout<<lcs(s1,s2)<<endl;
    }
}