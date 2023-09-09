#include<bits/stdc++.h>
#include"util.h"
using namespace std;
enum collRes {sepChain,doubleH,custom}; 
enum entryType {active,empty,deleted};

class HashTable{
    vector<list<pair<string,long long>>> hashTable;
    uint64_t count;
    uint64_t size;
    enum collRes type;
    bool hashType;
    uint64_t totProbeSearch;
    uint64_t totProbeDelete;
    uint64_t totCollision;
    vector<enum entryType> vis;

    // hash1 is used if true 
    // hash2 if false 

public:

    HashTable(uint64_t size,enum collRes type,bool hashType){
        this->size = size;
        count = 0;
        this->type = type;
        this->hashType = hashType;
        vis = vector<enum entryType>(size,empty);
        hashTable = vector<list<pair<string,long long>>>(size,list<pair<string,long long>>());
        totProbeSearch = 0;
        totProbeDelete = 0;
        totCollision = 0;
    }

    ~HashTable(){
        for(uint64_t i = 0; i < size;i ++){
            hashTable[i].clear();
        }
        hashTable.clear();
        count = 0;
        size = 0;
        totProbeSearch = 0;
        totCollision = 0;
    }   

    void operator=(HashTable &ht){
        this->size = ht.size;
        this->type = ht.type;
        this->hashType = ht.hashType;
        this->count = ht.count;
        this->totProbeSearch = ht.totProbeSearch;
        this->totCollision = ht.totCollision;
        this->totProbeDelete = ht.totProbeDelete;
        this->vis = ht.vis;
        this->hashTable = ht.hashTable;
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

    uint64_t hash2(string key){
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

    uint64_t auxHash(string key){
        return ((uint64_t)key[0]*1951+4103*(uint64_t)key[1]+(uint64_t)key[2]*1763)%size;
    }

    uint64_t doubleHash(uint64_t hash,string key,uint64_t i){
        return (hash + i*auxHash(key))%size;
    } 

    uint64_t customHash(uint64_t hash,string key,uint64_t i){
        return (hash + 27091*i*auxHash(key) + 11111*i*i)%size;
    }

    long long findSepChain(uint64_t hash,string key,bool probCalc=false){
        uint64_t probe = 1;
        long long val = 0;
        list<pair<string,long long>>::iterator it = hashTable[hash].begin();
        while(it != hashTable[hash].end()){
            if(it->first == key){
                val = it->second;
                break;
            }
            *it++;
            if(probCalc && it != hashTable[hash].end())probe++;
        }
        if(probCalc)totProbeSearch += probe;
        return val;
    }

    long long findClosedHash(uint64_t hash,string key,bool probCalc=false){
        uint64_t probe = 1;
        uint64_t i = 0;
        long long val = 0;
        uint64_t hashC = hash ;
        while(vis[hashC] != empty) {
            if(vis[hashC] == active && hashTable[hashC].front().first == key){
                val = hashTable[hashC].front().second;
                break;
            }
            else hashC = (type == doubleH) ? doubleHash(hash,key,++i) : customHash(hash,key,++i);
            if(probCalc && hashC != hash)probe++;       
            if(hashC == hash)break;     
        }
        if(probCalc)totProbeSearch += probe;
        return val;
    }

    void rehash(uint64_t size){
        vector<bool> primes(size*2,true);
        primeSieve(primes);
        HashTable newHash(getPrime(primes,size),type,hashType);
        list<pair<string,long long>>::iterator it;
        
        for(uint64_t i=0;i<size;i++){
            if(hashTable[i].size() != 0){
                it = hashTable[i].begin();
                while(it != hashTable[i].end()){
                    newHash.insert(it->first,it->second);
                    *it++;
                }
            }
        }

        hashTable = newHash.hashTable;
        vis = newHash.vis;
        size = newHash.size;
        count = newHash.count;
        totCollision = newHash.totCollision;
        totProbeSearch = newHash.totProbeSearch;
        totProbeDelete = newHash.totProbeDelete; 
    
    }

    bool insSepChain(uint64_t hash,string key,uint64_t val){
        if(!hashTable[hash].empty())totCollision ++;
        hashTable[hash].push_front({key,val});
        vis[hash] = active;
        count++;
        // if(count >= size/2)rehash();
        return true; 
    }

    bool insClosedHash(uint64_t hash,string key,uint64_t val){
        uint64_t hashC = hash;
        uint64_t i = 0;
        while(hashTable[hashC].size()){
            totCollision++;
            hashC = (type == doubleH) ? doubleHash(hash,key,++i) : customHash(hash,key,++i);
            if(hashC == hash)return false;
        }
        hashTable[hashC].push_front({key,val});
        vis[hashC] = active;
        count++;
        // if(count >= size/2)rehash();
        return true;
    }

    bool delSepChain(uint64_t hash,string key){
        list<pair<string,long long>>::iterator it = hashTable[hash].begin();
        while(it != hashTable[hash].end()){
            if(it->first == key){
                hashTable[hash].erase(it);
                if(hashTable[hash].size() == 0)vis[hash] = deleted;
                count--;
                return true;
            }
            *it++;
        }
        return false;
    }

    bool delClosedHash(uint64_t hash,string key){
        uint64_t hashC = hash;
        uint64_t i = 0;
        while(vis[hashC] != empty){
            if(vis[hashC] == active && hashTable[hashC].front().first == key){
                hashTable[hashC].clear();
                count--;
                vis[hashC] = deleted;
                return true;
            }
            else hashC = (type == doubleH) ? doubleHash(hash,key,++i) : customHash(hash,key,++i);
            if(hashC == hash)break;  
        }
        return false;
    }

    long long find(string key,bool probCalc=false){
        uint64_t hash = hashType ? hash1(key) : hash2(key);
        if(type == sepChain)return findSepChain(hash,key,probCalc);
        else return findClosedHash(hash,key,probCalc);
    }


    bool insert(string key,uint64_t val){
        if(find(key,false))return false;
        uint64_t hash = hashType ? hash1(key) : hash2(key);
        if(type == sepChain)return insSepChain(hash,key,val);
        else return insClosedHash(hash,key,val);
    }

    bool erase(string key){
        uint64_t hash = hashType ? hash1(key) : hash2(key);
        if(type == sepChain)return delSepChain(hash,key);
        else return delClosedHash(hash,key);
    }

    void print(){
        list<pair<string,long long>>::iterator it;
        for(uint64_t i=0;i<size;i++){
            if(hashTable[i].size() != 0){
                cout<<i<<" : ";
                it = hashTable[i].begin();
                while(it != hashTable[i].end()){
                    cout<<"("<<it->first<<" , "<<it->second<<") ";	
                    *it++;
                }
                cout<<endl;
            }
        }
    }

    inline uint64_t totCollisionCount() const{return totCollision;}
    inline uint64_t totProbSearch() const{return totProbeSearch;}

    vector<pair<string,long long>> retAll(){
        vector<pair<string,long long>> all;
        list<pair<string,long long>>::iterator it;
        for(uint64_t i=0;i<size;i++){
            if(hashTable[i].size() != 0){
                it = hashTable[i].begin();
                while(it != hashTable[i].end()){
                    all.push_back({it->first,it->second});
                    *it++;
                }
            }
        }
        return all;
    }

};