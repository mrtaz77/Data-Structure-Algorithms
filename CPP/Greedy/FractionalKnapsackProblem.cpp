#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    long int W;
    cin>>n>>W;
    
    pair<double,double> items[n];
    for(int i=0;i<n;i++){
        cin>>items[i].first>>items[i].second;
        items[i].first = items[i].first/items[i].second;
    }

    sort(items,items+n);

    double sum = 0;
    for(int i=n;W>0 && i>=0;i--){
        if(items[i].second < W){
            sum += (items[i].first*items[i].second);
            W -= items[i].second;
        }
        else{
            sum += items[i].first*W;
            break;
        }
    }
    printf("%.12f",sum);
}