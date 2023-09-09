#include<bits/stdc++.h>
#include"hashTable2.h"
#include"util.h"
using namespace std;
int main(){
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    int n;
    vector<bool> primes(1000007,true);
    primeSieve(primes);
    cin >> n;
    n = getPrime(primes,n);

    HashTable2 table(n,sepChain,true);

    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        char cmd;
        vector<string> keys;
        string key1,key2;
        long long val;
        iss >> cmd;

        switch(cmd){
            case 'I':
                if(iss>>key1 && iss>>key2 && iss>>val)cout<<boolalpha<<table.insert(key1,key2,val)<<endl;
                break;
            case 'F':
                while(iss>>key1){
                    keys.push_back(key1);
                }
                if(keys.size() == 1){
                    auto c = table.find(keys[0]);
                    cout<<"[";
                    for(int i=0; i<c.size(); i++){
                        cout<<"("<<c[i].first<<","<<c[i].second<<")";
                        if(i!=c.size()-1)cout<<", ";
                    }
                    cout<<"]\n";
                }
                else{
                    val = table.find(keys[0],keys[1]);
                    if(val)cout<<val<<endl;
                    else cout<<"null"<<endl;
                }
                keys.clear();
                break;
        }
    }
}