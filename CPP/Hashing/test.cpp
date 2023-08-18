#include<bits/stdc++.h>
#include"hashTable.h"
using namespace std;



int main(){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    int n,m;
    cin >> n >> m;
    vector<bool> primes(n,true);
    primeSieve(primes);
    
    n = getPrime(primes,n);

    auto words = rwg(100,5,10);

    HashTable ht(getPrime(primes,10),doubleH,false);
    set<long long> uniqueH1;
    set<long long> uniqueH2;
    set<long long> uniqueH3;

    for(string word : words){
        long long h1 = ht.hash1(word);
        long long h2 = ht.hash2(word);
        long long h3 = ht.auxHash(word);
        // cout<<word<<" : "<<h1<<" "<<h2<<" "<<h3<<endl;
        uniqueH1.insert(h1);
        uniqueH2.insert(h2);
        uniqueH3.insert(h3);
    }
    cout << uniqueH1.size() << " " << uniqueH2.size() << " " << uniqueH3.size() <<endl;

    long long i = 0;
    for(string word : words){
        cout<<word<<" : ";
        cout<<boolalpha <<ht.insert(word,++i)<<endl;
    }

    ht.print();

    for(string word : words){
        cout<<word<<" : ";
        cout<<ht.find(word,true)<<endl;
    }
    cout<<ht.totProbSearch()<<endl;
}