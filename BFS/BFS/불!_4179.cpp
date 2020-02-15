//
//  불!_4179.cpp
//  BFS
//
//  Created by jiho park on 2020/02/15.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>

#define endl "\n"
using namespace std;

//불 먼저 옮겨야 하는 것이 핵심.

char a[1000][1000];
int d[1000][1000];
int n, m;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m;
    
    queue<pair<int,int>> Fire, nFire;
    queue<pair<int,int>> Jihun, nJihun;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> a[i][j];
            if(a[i][j]=='J'){
                Jihun.emplace(i,j);
                d[i][j]=1;
                a[i][j]='.';
            }else if(a[i][j]=='F'){
                Fire.emplace(i,j);
            }
        }
    }
    
    while(!Jihun.empty()){
        while(!Fire.empty()){//주변에 태울 수 있는 부분은 모두 태우고 새롭게 태운 부분을 nfire에 옮기기 때문에 방문 체크를 해줄 필요가 없음.
            int x,y;
            tie(x,y) = Fire.front();
            Fire.pop();
            for(int i=0; i<4; i++){
                int nx,ny;
                nx = x+dx[i];
                ny = y+dy[i];
                if(nx<0 || nx>=n || ny<0 || ny>= m) continue;
                if(a[nx][ny]=='#' || a[nx][ny]=='F') continue;
                a[nx][ny]='F';
                nFire.emplace(nx,ny);
            }
        }
        
        while(!Jihun.empty()){
            int x,y;
            tie(x,y) = Jihun.front();
            Jihun.pop();
            for(int i=0; i<4; i++){
                int nx,ny;
                nx = x+dx[i];
                ny = y+dy[i];
                if(nx<0 || nx>=n || ny<0 || ny>=m){//지훈이가 벗어난 경우.
                    cout << d[x][y];
                    return 0;
                }
                if(a[nx][ny]=='#' || a[nx][ny]=='F') continue;
                if(d[nx][ny]>0) continue;
                nJihun.emplace(nx,ny);
                d[nx][ny] = d[x][y]+1;//거리 계산.
            }
        }
        
        Jihun = nJihun;
        Fire = nFire;
        nJihun=queue<pair<int,int>>();
        nFire=queue<pair<int,int>>();
    }
    
    cout << "IMPOSSIBLE";
    
    return 0;
}
