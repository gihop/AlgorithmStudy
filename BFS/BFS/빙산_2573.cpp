//
//  빙산_2573.cpp
//  BFS
//
//  Created by jiho park on 2020/02/10.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>
#include <vector>
#include <cstring>

#define endl "\n"
using namespace std;

//bfs로 해결.

vector<vector<int>>now(300, vector<int>(300,0));
bool check[300][300];
int n,m;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> now[i][j];
        }
    }
    
    int ans;
    
    for(ans=0; ;ans++){
        int ice_count=0;
        vector<vector<int>> next(300, vector<int>(300,0));//다음 빙산모양 저장.
        memset(check, false, sizeof(check));//방문 체크 초기화.
        bool no_ice=true;//모든 빙산이 0이될 때까지 끝나지 않으면 true.
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(now[i][j]>0 && ice_count>0 && !check[i][j]){//빙산이 두 개로 나뉘었을 경우.
                    cout << ans;
                    return 0;
                }
                if(now[i][j]>0){
                    no_ice=false;
                    ice_count++;
                    queue<pair<int,int>> q;
                    q.emplace(i,j);
                    check[i][j]=true;
                    while(!q.empty()){
                        int x,y;
                        tie(x,y) = q.front();
                        q.pop();
                        int zero_count=0;
                        for(int k=0; k<4; k++){
                            int nx, ny;
                            nx = x+dx[k];
                            ny = y+dy[k];
                            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                            if(check[nx][ny]) continue;
                            if(now[nx][ny]==0){
                                zero_count++;
                                continue;
                            }
                            q.emplace(nx,ny);
                            check[nx][ny]=true;
                        }
                        int next_ice = now[x][y]-zero_count;
                        if(next_ice < 0)
                            next_ice=0;
                        next[x][y]=next_ice;//주변이 물인 갯수 만큼 빼고 다음 빙하정보 저장.
                    }
                }
            }
        }
        if(no_ice){
            cout << 0;
            return 0;
        }
        now=next;//다음 빙하를 현재 빙하로 옮김.
    }
    
    return 0;
}
