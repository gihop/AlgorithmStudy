//
//  레이저_통신_6087.cpp
//  BFS
//
//  Created by jiho park on 2020/02/18.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>

#define endl "\n"
using namespace std;

char a[100][100];
int check[100][100];
int n,m;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};
int ans=999999999;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> m >> n;
    
    int ax,ay;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> a[i][j];
            if(a[i][j]=='C'){
                ax=i;
                ay=j;
            }
        }
    }
    check[ax][ay]=0;
    queue<tuple<int,int,int,int>> q;
    q.emplace(ax,ay,0,-1);
    
    while(!q.empty()){
        int x,y,cnt,dirct;
        tie(x,y,cnt,dirct) = q.front();
        q.pop();
        if(a[x][y]=='C' && (x!=ax || y!=ay)){
            if(ans > cnt)
                ans = cnt;
            continue;
        }
        for(int i=0; i<4; i++){
            int nx, ny, nCnt;
            if(dirct==-1 || dirct == i)
                nCnt = cnt;
            else if(dirct != i)
                nCnt = cnt+1;
            nx = x+dx[i];
            ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
            if(check[nx][ny]!=0 && check[nx][ny]<nCnt) continue;
            if(a[nx][ny]=='*') continue;
            q.emplace(nx,ny,nCnt,i);
            check[nx][ny]=nCnt;
        }
    }
    
    cout << ans;
    
    return 0;
}
