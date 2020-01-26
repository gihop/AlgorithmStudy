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
    
    cin >> k >> n >> m;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> a[i][j];
    
    d[0][0][0]=0;
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
            if(nx<0 || nx>=n || ny<0 || ny >=m) continue;
            if(d[nx][ny][z] > 0 || a[nx][ny] == 1) continue;
            if(i<8 && z<k){
                d[nx][ny][z+1] = d[x][y][z]+1;
                if(nx == n-1 && ny == m-1) break;
                q.emplace(nx,ny,z+1);
            }else{
                d[nx][ny][z] = d[x][y][z]+1;
                if(nx == n-1 && ny == m-1) break;
                q.emplace(nx,ny,z);
            }
        }
    }
    
    int ans=-1;
    for(int i=0; i<=k; i++){
        if(ans==-1)
            ans = d[n-1][m-1][i];
        else if(ans > d[n-1][m-1][i])
            ans = d[n-1][m-1][i];
    }
    
    cout << ans;
    
    return 0;
}
