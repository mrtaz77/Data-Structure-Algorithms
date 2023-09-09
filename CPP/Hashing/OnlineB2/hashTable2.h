#include<bits/stdc++.h>
#include"hashTable.h"
using namespace std;

class HashTable2{
    vector<list<pair<string,HashTable*>>> hashTable2;
    uint64_t count;
    uint64_t size;
    enum collRes type;
    bool hashType;
    uint64_t totProbeSearch;
    uint64_t totProbeDelete;
    uint64_t totCollision;
    vector<enum entryType> vis;


public:
    HashTable2(uint64_t size,enum collRes type,bool hashType){
        this->size = size;
        count = 0;
        this->type = type;
        this->hashType = hashType;
        totProbeSearch = 0;
        totProbeDelete = 0;
        totCollision = 0;
        vis = vector<enum entryType>(size,empty);
        hashTable2 = vector<list<pair<string, HashTable*>>>(size, list<pair<string, HashTable*>>());
    }


    ~HashTable2(){
        for(uint64_t i = 0; i < size;i ++){
            hashTable2[i].clear();
        }
        hashTable2.clear();
        count = 0;
        size = 0;
        totProbeSearch = 0;
        totCollision = 0;
    }

    uint64_t hash1(string key){
        uint64_t hash = 0;
        uint64_t coeff = 1;
        uint64_t c = 23;
        for(int i=0;i<key.length();i++){
            hash = (hash + (uint64_t)key[i]*coeff)%size;
            coeff = (coeff*c)%size;
        }
        return hash%size;
    }
    long long find(string key1,string key2){
        uint64_t hash = hash1(key1);
        long long val = 0;
        list<pair<string,HashTable*>>::iterator it = hashTable2[hash].begin();
        while(it != hashTable2[hash].end()){
            if(it->first == key1){
                val = it->second->find(key2);
            }
            *it++;
        }
        return val;
    }

    vector<pair<string,long long>> find(string key){
        uint64_t hash = hash1(key);
        vector<pair<string,long long>> ans;
        list<pair<string,HashTable*>>::iterator it = hashTable2[hash].begin();
        while(it != hashTable2[hash].end()){
            if(it->first == key){
                ans = it->second->retAll();
            }
            *it++;
        }
        return ans;
    }

    bool insert(string key1,string key2,long long val){
        if(find(key1,key2))return false;
        uint64_t hash = hash1(key1);
        list<pair<string,HashTable*>>::iterator it = hashTable2[hash].begin();
        while(it != hashTable2[hash].end()){
            if(it->first == key1){
                return it->second->insert(key2,val);
            }
        }
        hashTable2[hash].push_front({key1,new HashTable(size,type,hashType)});
        hashTable2[hash].front().second->insert(key2,val);
    }
};