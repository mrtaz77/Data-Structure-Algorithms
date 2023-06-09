#include<bits/stdc++.h>
#include"GraphUtil.h"
using namespace std;

int rotTime(vector<vector<int>> &grid,int row,int col){
    vector<vector<int>> vis(row,vector<int>(col,0));
    int n = grid.size();
    int m = grid[0].size();
    queue<pair<int,pair<int,int>>> q;
    int freshCount = 0;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(grid[i][j] == 1)freshCount++;
            if(grid[i][j] == 2){
                q.push({0,{i,j}});
                vis[i][j] = 2;
            }
            else vis[i][j] = 0;
        }
    }

    int time = 0;
    int delR[] = {-1,0,1,0};
    int delC[] = {0,1,0,-1};
    int count = 0;
    while(!q.empty()){
        time = q.front().first;
        int i = q.front().second.first;
        int j = q.front().second.second;
        q.pop();
        for(int k = 0; k < 4; k++){
            int nrow = i+delR[k];
            int ncol = j+delC[k];
            if(nrow>=0 && ncol>=0 && nrow<n && ncol<m){
                if(grid[nrow][ncol] == 1 && vis[nrow][ncol] != 2){
                    count++;
                    vis[nrow][ncol] = 2;
                    q.push({time+1,{nrow,ncol}});
                }
            }
        }
    }

    if(count != freshCount)return -1;
    return time;
}


int main(){

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n,m,o;
    cin>>n>>m;
    vector<vector<int>> grid(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>o;
            grid[i].push_back(o);
        }
    }

    cout<<"Time taken : "<<rotTime(grid,n,m)<<endl;
}