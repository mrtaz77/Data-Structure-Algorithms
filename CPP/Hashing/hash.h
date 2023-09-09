#include<bits/stdc++.h>
using namespace std;

uint64_t hash1(string key,uint64_t size){
    uint64_t hash = 0;
    uint64_t coeff = 1;
    uint64_t c = 23;
    for(int i=0;i<key.length();i++){
        hash = (hash + (uint64_t)key[i]*coeff)%size;
        coeff = (coeff*c)%size;
    }
    return hash%size;
}

uint64_t hash2(string key,uint64_t size){
    int i;
    uint64_t hash = 0;
    for(i=0;i<key.length()/2;i++){
        hash = (1307*hash + (uint64_t)key[key.length()-i-1]);
    }

    for(;i<key.length();i++){
        hash = (1733*hash + (uint64_t)key[key.length()-i-1]);
    }
    return hash%size;
}

uint64_t auxHash(string key,uint64_t size){
    return ((uint64_t)key[0]*1951+4103*(uint64_t)key[1]+(uint64_t)key[2]*1763)%size;
}

uint64_t doubleHash(uint64_t hash,string key,uint64_t i,uint64_t size){
    return (hash + i*auxHash(key,size))%size;
} 

uint64_t customHash(uint64_t hash,string key,uint64_t i,uint64_t size){
    return (hash + 27091*i*auxHash(key,size) + 11111*i*i)%size;
}