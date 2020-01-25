//
//  벽_부수고_이동하기2_14442.cpp
//  BFS
//
//  Created by jiho park on 2020/01/25.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>

using namespace std;

//dfs는 모든 경우의 수를 봐야해서 bfs가 효율적임.
//k 입력이 다른 경우의 수를 추가하는 것이라고 생각해야 함.
//k가 1이면 경우의 수가 2개가 되는 것, k는 1~10범위이므로 11가지의 경우의 수가 필요함.
//따라서 d배열에 11임.

int a[1000][1000];
int d[1000][1000][11];
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int main(){
    int n, m, k;
    
    cin >> n >> m >> k;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            scanf("%1d", &a[i][j]);//0100입력에서 0하나만 입력받는 법.
    
    d[0][0][0]=1;
    queue<tuple<int,int,int>> q;
    q.push(make_tuple(0, 0, 0)); //=q.emplace(0,0,0); 같은 것.
    
    while(!q.empty()){
        int x,y,z;
        tie(x,y,z) = q.front();
        q.pop();
        for(int i=0; i<4; i++){
            int nx, ny;
            nx = x+dx[i];
            ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
            if(a[nx][ny]==0 && d[nx][ny][z] == 0){//다음에 방문할 곳이 0인지 확인하는 것이기 때문에 z+1 경우와 따로 검사해야 함.
                q.emplace(nx,ny,z);
                d[nx][ny][z] = d[x][y][z]+1;
            }
            if(a[nx][ny]==1 && z < k && d[nx][ny][z+1] == 0){
                q.emplace(nx,ny,z+1);
                d[nx][ny][z+1] = d[x][y][z]+1;
            }
        }
    }
    
    int ans=-1;
    for(int i=0; i<=k; i++){
        if(d[n-1][m-1][i] == 0) continue;
        if(ans==-1)
            ans = d[n-1][m-1][i];
        else if(d[n-1][m-1][i] < ans)
            ans = d[n-1][m-1][i];
    }
    
    cout << ans;
    
    return 0;
}
