#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    long int *a;
    a = new long int[n];
    int count = 0;
    //works but flag is redundant
    /* bool flag = false;
    for(int i = 0; i < n;i++){
        cin >> a[i];
        if(a[i] == 0 && flag){
            flag = false;
            count++;
        }
        else if(a[i] == 1 && !flag){
            count++;
            flag = true;
        }
    } */
    for(int i = 0;i < n;i++){
        cin >> a[i];
        if(count%2 != 0)a[i] ^= 1;
        if(a[i] == 0)continue;
        else count++;
    }
    cout<<count<<endl;
}