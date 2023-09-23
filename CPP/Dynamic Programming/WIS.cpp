#include <bits/stdc++.h>
using namespace std;
class Job{
public:
    int start;
    int finish;
    int value;
    Job(int start=0, int finish=0, int value=0){
        this->start = start;
        this->finish = finish;
        this->value = value;
    }
    friend ostream& operator<<(ostream& out,const Job& job);
};

ostream& operator<<(ostream& out,const Job& job){
    out << "(" << job.start << "," << job.finish << "," << job.value << ")";
}

bool compare(const Job& a, const Job& b){
    if(a.finish != b.finish)return a.finish<b.finish;
    else return a.value > b.value;
}

int latestNonConflict(Job jobs[],int index){
    int low = 0, high = index - 1;
    int mid;
    while(low <= high){
        mid = (low + high)/2;
        if(jobs[mid].finish <= jobs[index].start){
            if(jobs[mid+1].finish <= jobs[index].start)low = mid + 1;
            else return mid;
        }
        else high = mid - 1;
    }
    return -1;
}

int wis(Job jobs[],int n){
    int dp[n];
    memset(dp,0,sizeof(dp));
    dp[0] = jobs[0].value; 
    cout<<dp[0]<<" ";
    for(int i=1;i<n;i++){
        int included = jobs[i].value;
        int excluded = dp[i-1];
        int nonConflict = latestNonConflict(jobs,i);
        if(nonConflict != -1)included += dp[nonConflict];
        dp[i] = max(included,excluded);
        cout<<dp[i]<<" ";
    }
    cout<<endl;
    return dp[n-1];
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        Job jobs[n];
        for(int i = 0; i < n; i++){
            cin >> jobs[i].start>> jobs[i].finish>> jobs[i].value;
        }
        sort(jobs,jobs+n,compare);
        for(int i = 0; i < n; i++)cout<<jobs[i]<<" ";
        cout<<endl;
        cout<<wis(jobs,n)<<endl;
    }

}