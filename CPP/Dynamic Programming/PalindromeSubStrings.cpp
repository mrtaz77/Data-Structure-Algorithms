#include <bits/stdc++.h>
using namespace std;
int countP(string str)
{
    int n = str.length();
    int count = 0;

    bool palindrome[n][n];
    memset(palindrome, false, sizeof(palindrome));

    for (int i = 0; i < n; i++){
        palindrome[i][i] = true;
    }// diagonal elements 

    for (int gap = 2; gap <=n; gap++) {
        for (int i = 0; i < n-gap; i++) {
            int j = i + gap -1;

            if(i==j-1)palindrome[i][j]=(str[i]==str[j]);
            else palindrome[i][j]=(str[i]==str[j] && palindrome[i+1][j-1]);
            
            if(palindrome[i][j])count++;
        }
    }

    return count+n;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while(t--){
        string str;
        cin >> str;
        cout<<countP(str)<<endl;
    }
}