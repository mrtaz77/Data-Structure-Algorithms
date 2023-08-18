#include<bits/stdc++.h>
using namespace std;

uint64_t hash1(string key,int size){
    uint64_t hash = 0;
    uint64_t coeff = 1;
    uint64_t c = 31;
    for(int i=0;i<key.length();i++){
        hash = (hash + (uint64_t)key[i]*coeff)%size;
        coeff = (coeff*c)%size;
    }
    return hash%size;
}

uint64_t hash2(string key,int size){
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

void test_h1(int n)
{
    set<string> data;
    set<int> codes;
    while (data.size() < 100)
    {
        string s;
        for (int j = 0; j < 7; j++)
        {
            char c = 'a' + rand() % 26;
            s += c;
        }
        data.insert(s);
    }
    for (auto s : data)
    {
        int hash_code = hash1(s,n) % n;
        codes.insert(hash_code);
    }
    cout << "H1 is " << codes.size() << "% effective" << endl;
}
void test_h2(int n)
{
    set<string> data;
    set<int> codes;
    while (data.size() < 100)
    {
        string s;
        for (int j = 0; j < 7; j++)
        {
            char c = 'a' + rand() % 26;
            s += c;
        }
        data.insert(s);
    }
    for (auto s : data)
    {
        int hash_code = hash2(s, n) % n;
        // cout << hash_code << " " << endl;
        codes.insert(hash_code);
    }
    cout << "H2 is " << codes.size() << "% effective" << endl;
}


int main(){
    test_h1(100);
    test_h2(100);
}