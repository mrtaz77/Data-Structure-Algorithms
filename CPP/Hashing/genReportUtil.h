#include<bits/stdc++.h>
using namespace std;
string charGen(char ch,int n){
    string str;
    for(int i=0;i<n;i++)str+=ch;
    return str;
}

void genReport(vector<uint64_t> collision,vector<long double> avgProbe){
    int i = 0;
    int j = 0;
    int n = 5000;
    while(i < collision.size()){
        cout<<charGen('_',107)<<endl;
        cout<<"|             |                 |                Hash1               |                Hash2               |"<<endl;
        cout<<"|    Hash     |Collision        |____________________________________|____________________________________|"<<endl;
        cout<<"|    Table    |Resolution       |       #  of      |     Average     |       #  of      |     Average     |"<<endl;
        cout<<"|    Size     |Technique        |    Collisions    |     Probes      |    Collisions    |     Probes      |"<<endl;
        cout<<"|_____________|_________________|__________________|_________________|__________________|_________________|"<<endl;
        cout<<"|             |Chaining         |"<<setw(18)<<left<<collision[i++]<<"|"<<setw(17)<<left<<avgProbe[j++]<<"|"<<setw(18)<<left<<collision[i++]<<"|"<<setw(17)<<left<<avgProbe[j++]<<"|"<<endl;
        cout<<"|             |_________________|__________________|_________________|__________________|_________________|"<<endl;        
        cout<<"|    "<<setw(9)<<left<<n<<"|Double Hashing   |"<<setw(18)<<left<<collision[i++]<<"|"<<setw(17)<<left<<avgProbe[j++]<<"|"<<setw(18)<<left<<collision[i++]<<"|"<<setw(17)<<left<<avgProbe[j++]<<"|"<<endl;
        cout<<"|             |_________________|__________________|_________________|__________________|_________________|"<<endl;
        cout<<"|             |Custom Hashing   |"<<setw(18)<<left<<collision[i++]<<"|"<<setw(17)<<left<<avgProbe[j++]<<"|"<<setw(18)<<left<<collision[i++]<<"|"<<setw(17)<<left<<avgProbe[j++]<<"|"<<endl;
        cout<<"|_____________|_________________|__________________|_________________|__________________|_________________|"<<endl;
        cout<<endl;
        cout<<endl;
        n+=5000;
        if(n==15000)n+=5000;
    }
}