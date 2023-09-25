#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    long int *a;
    pair<int,int> *tasks = new pair<int,int>[n];
    string s = "";

    for(int i = 0; i < n; i++){
        cin >> tasks[i].second;
        cin >> tasks[i].first;
    }
    sort(tasks, tasks+n);
    cout<<"==========\n";
    int count = 0;
    int k = 0;
    int m = 1;
    cout<<tasks[m].second<<" "<<tasks[m].first<<endl;
    while(m < n){
        if(tasks[m].second < tasks[k].first)m+=1;
        else{
            count++;
            cout<<tasks[m].second<<" "<<tasks[m].first<<endl;
            k = m;
            m+=1;
        }
    }
    cout<<count<<endl;
}