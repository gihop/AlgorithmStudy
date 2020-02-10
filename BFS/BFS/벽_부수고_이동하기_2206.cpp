//
//  벽_부수고_이동하기_2206.cpp
//  BFS
//
//  Created by jiho park on 2020/02/09.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

#define endl "\n"
using namespace std;

//bfs로 문제 해결.

int n,m;
int a[1000][1000];
int d[1000][1000][2];//이동한 거리 저장.
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};
int ans;

int main(){
    cin >> n >> m;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            scanf("%1d", &a[i][j]);
    
    queue<tuple<int,int,int>> q;
    q.emplace(0,0,0);
    d[0][0][0]=1;
    
    while(!q.empty()){
        int x,y, crush;
        tie(x,y,crush) = q.front();
        q.pop();
        for(int i=0; i<4; i++){
            int nx,ny;
            nx = x+dx[i];
            ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
            if(d[nx][ny][crush]>0) continue;//이미 방문한 칸인 경우.
            if(crush>0 && d[nx][ny][crush-1]>0) continue;//벽을 깬 상태에서 벽을 깨기 전에 방문했던 곳인 경우.
            if(a[nx][ny]==0){//0이면 이동.
                q.emplace(nx,ny,crush);
                d[nx][ny][crush] = d[x][y][crush]+1;
            }else if(a[nx][ny]==1 && crush==0){//아직 벽을 깬적이 없을 경우.
                q.emplace(nx,ny,crush+1);
                d[nx][ny][crush+1] = d[x][y][crush]+1;
            }
        }
    }
    
    if(d[n-1][m-1][0]==0 && d[n-1][m-1][1]==0){//마지막 칸으로 도달 못한 경우.
        cout << -1;
        return 0;
    }
    else if(d[n-1][m-1][0]>0)
        ans=d[n-1][m-1][0];
    if(d[n-1][m-1][1]>0 && ans==0)
        ans=d[n-1][m-1][1];
    else if(d[n-1][m-1][1]>0 && d[n-1][m-1][1]<ans)
        ans=d[n-1][m-1][1];
    cout << ans;
    
    return 0;
}
