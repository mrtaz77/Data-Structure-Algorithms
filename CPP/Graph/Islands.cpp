#include<bits/stdc++.h>
#include"GraphUtil.h"
using namespace std;

void bfs(int i,int j,vector<vector<char>> &grid,vector<vector<int>> &vis){
    int n = grid.size();
    int m = grid[0].size();
    vis[i][j] = 1;
    queue<pair<int,int>> q;
    q.push({i,j});
    while(!q.empty()){
        int row = q.front().first;
        int col = q.front().second;
        q.pop();
        for(int delR = -1; delR <= 1; delR++){
            for(int delC = -1; delC <= 1; delC++){
                if(row+delR>=0 && row+delR<n && col+delC>=0 && col+delC<m){
                    if(!vis[row+delR][col+delC] && grid[row+delR][col+delC] != '0'){
                        vis[row+delR][col+delC] = 1;
                        q.push({row+delR,col+delC});
                    }
                }
            }
        }
    }
}

int numIslands(vector<vector<char>> &grid){
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> vis(n,vector<int>(m,0));
    int count = 0;
    for(int i = 0; i < n ; i++){
        for (int j = 0; j < m ; j++)
        {
            if(!vis[i][j] && grid[i][j] != '0'){
                count++;
                bfs(i,j,grid,vis);
            }
        }
    }
    return count;
}

int main(){

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n,m;
    char c;
    cin>>n>>m;
    vector<vector<char>> grid(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>c;
            grid[i].push_back(c);
        }
    }

    cout<<"Number of islands "<<numIslands(grid)<<endl;
}