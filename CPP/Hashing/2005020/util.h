#include<bits/stdc++.h>
#define SEED 1331
using namespace std;
char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

void primeSieve(vector<bool> &sieve){
    sieve[0] = sieve[1] = false;

    for(int i = 3;i*i < sieve.size();i+=2){
        if(sieve[i]){
            for(int j = i*i;j < sieve.size();j+=i){
                sieve[j] = false;
            }
        }
    }
}

long long getPrime(vector<bool> &sieve,long long n){
    if(n < 3)return 2;
    if(n%2 == 0)n += 1;
    if(sieve[n])return n;
    for(long long i = n;i < 2*n ; i+=2)if(sieve[i])return i;
    return -1;
}

vector<string> rwg(long long n,int low,int high){
    srand(SEED);
    set<string> words;

    while(words.size() < n){
        int len = rand() % (high-low+1) + low; 
        string str;
        for (int i=0;i < len;i++) {
            int index = rand()%26;
            str += alphabet[index];
        }
        words.insert(str);
    }
    return vector<string>(words.begin(), words.end());
}
