//
//  말이_되고픈_원숭이_1600.cpp
//  BFS
//
//  Created by jiho park on 2020/01/26.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2, 0, 1, 0, -1};
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1, 1, 0, -1, 0};
int a[200][200];
int d[200][200][31];

int main(){
    int n, m, k;
    
    cin >> k >> m >> n;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> a[i][j];
    
    d[0][0][0]=1;//1로 표기를 해야 처음에 말로 이동을 했을 때 다시 안돌아옴. 그래서 맨 뒤에 1을 빼줌.
    queue<tuple<int,int,int>> q;
    q.emplace(0, 0, 0);
    
    while(!q.empty()){
        int x,y,z;
        tie(x,y,z) = q.front();
        q.pop();
        for(int i=0; i<12; i++){
            int nx, ny;
            nx = x+dx[i];
            ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny >=m) continue;//맵에서 벗어난 경우.
            if(d[nx][ny][z] > 0)continue;//이동할 곳이 이미 갔던 곳인 경우.
            if(a[nx][ny] == 1) continue;//이동할 곳이 벽인 경우.
            if(z>0)//메모리 초과 해결 부분. 말로 이동한 후에 이전 경로에서 이미 갔던 곳은 다시 큐에 넣으면 안됨.
                if(d[nx][ny][z-1] > 0) continue;
            if(i<8 && z<k && d[nx][ny][z+1] == 0){//말로 이동하는 경우.
                d[nx][ny][z+1] = d[x][y][z]+1;
                if(nx == n-1 && ny == m-1) break;
                q.emplace(nx,ny,z+1);
            }else if(i>=8){//인접한 곳으로 이동하는 경우.
                d[nx][ny][z] = d[x][y][z]+1;
                if(nx == n-1 && ny == m-1) break;
                q.emplace(nx,ny,z);
            }
        }
    }
    
    int ans=0;
    for(int i=0; i<=k; i++){
        if(d[n-1][m-1][i]==0) continue;
        if(ans==0)
            ans = d[n-1][m-1][i];
        else if(ans > d[n-1][m-1][i])
            ans = d[n-1][m-1][i];
    }
    
    cout << ans-1;
    
    return 0;
}
