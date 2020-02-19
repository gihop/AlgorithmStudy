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

//쉬워보이지만 생각을 잘해야 하는 문제.
//큐에 방향을 같이 삽입해서 다음에 갈 방향이 이전에 움직였던 방향과 다르면 cnt+1을 한다.

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
        if(a[x][y]=='C' && (x!=ax || y!=ay)){//다른 C에 도착했을 경우.
            if(ans > cnt)
                ans = cnt;
            continue;
        }
        for(int i=0; i<4; i++){
            int nx, ny, nCnt;
            if(dirct==-1 || dirct == i)//-1은 처음 C에서 출발할 때를 말하고 방향이 같게 움직이면 cnt는 그대로
                nCnt = cnt;
            else if(dirct != i)//방향이 다르게 움직이면 cnt+1.
                nCnt = cnt+1;
            nx = x+dx[i];
            ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
            if(check[nx][ny]!=0 && check[nx][ny]<nCnt) continue;//이미 방문했던 칸인데 cnt값이 check에 저장된 값보다 큰 경우.
            if(a[nx][ny]=='*') continue;
            q.emplace(nx,ny,nCnt,i);
            check[nx][ny]=nCnt;
        }
    }
    
    cout << ans;
    
    return 0;
}
