#include<bits/stdc++.h>
#include"hashTable.h"
#include"genReportUtil.h"
#define MAX 1000007
using namespace std;

int main(){
    // freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    int n;
    cin >> n;

    vector<bool> primes(MAX,true);
    primeSieve(primes);

    auto words = rwg(10000,5,10);

    srand(SEED);
    random_device rd;
    mt19937 gen(rd());

    vector<string> shuffled(words.begin(),words.begin()+(n < 10000 ? n : 10000));
    shuffle(shuffled.begin(),shuffled.end(),gen);

    vector<uint64_t> totColl;
    vector<long double>totProbe;
        
    HashTable sep1(getPrime(primes,n),sepChain,true);
    HashTable sep2(getPrime(primes,n),sepChain,false);
    HashTable double1(getPrime(primes,n),doubleH,true);
    HashTable double2(getPrime(primes,n),doubleH,false);
    HashTable custom1(getPrime(primes,n),custom,true);
    HashTable custom2(getPrime(primes,n),custom,false);

    uint64_t i = 1;
    for(string words : words){
        sep1.insert(words,i);
        sep2.insert(words,i);
        double1.insert(words,i);
        double2.insert(words,i);
        custom1.insert(words,i);
        custom2.insert(words,i);
        i++;
        if(i > n)break;
    }

    totColl.push_back(sep1.totCollisionCount());
    totColl.push_back(sep2.totCollisionCount()) ;
    totColl.push_back(double1.totCollisionCount()) ;
    totColl.push_back(double2.totCollisionCount()) ;
    totColl.push_back(custom1.totCollisionCount()) ;
    totColl.push_back(custom2.totCollisionCount()) ;


    

    i = 1 ;
    for(string word:shuffled){
        sep1.find(word,true);
        sep2.find(word,true);
        double1.find(word,true);
        double2.find(word,true);
        custom1.find(word,true);
        custom2.find(word,true);
        if(++i > 1000)break;
    }

    totProbe.push_back(sep1.totProbSearch()/(long double)1000);
    totProbe.push_back(sep2.totProbSearch()/(long double)1000);
    totProbe.push_back(double1.totProbSearch()/(long double)1000);
    totProbe.push_back(double2.totProbSearch()/(long double)1000);
    totProbe.push_back(custom1.totProbSearch()/(long double)1000);
    totProbe.push_back(custom2.totProbSearch()/(long double)1000);


    genReport(totColl,totProbe,n);
}