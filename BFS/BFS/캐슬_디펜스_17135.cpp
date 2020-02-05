//
//  캐슬_디펜스_17135.cpp
//  BFS
//
//  Created by jiho park on 2020/02/04.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

//궁수를 n-1 위치에 놓고 거리를 1로 시작하거나 궁수를 n 위치에 놓고 거리를 0으로 시작하는거나 두 가지 모두 맞다.


int n, m, d;
int a[16][15];
int check[16][15];
int dx[]={0, 0, -1};
int dy[]={1, -1, 0};
int ans;

void go(vector<int> v, int idx){
    if(v.size()==3){
        int map[16][15];//맵 복사.
        for(int i=0; i<n+1; i++){
            for(int j=0; j<m; j++){
                map[i][j] = a[i][j];
            }
        }
        int enemy=0;
        while(true){
            bool finish=true;
            for(int i=n-1; i>=0; i--){
                for(int j=0; j<m; j++){
                    if(map[i][j]==1){//적이 발견되지 않는다면 게임 종료.
                        finish=false;
                        break;
                    }
                }
                if(!finish)
                    break;
            }
            if(finish){
                if(enemy > ans)
                    ans = enemy;
                return;
            }
            vector<pair<int,int>> dead[3];//각 궁수가 쏠 수 있는 적을 담음.
            for(int i=0; i<3; i++){
                int ax=n, by=v[i];//궁수의 위치를 벡터에서 받아옴.
                queue<tuple<int,int,int>> q;
                q.emplace(ax,by,0);
                memset(check, false, sizeof(check));
                check[ax][by]=true;
                bool found=false;
                int distance=0;
                while(!q.empty()){
                    int x, y, dist;
                    tie(x,y,dist) = q.front();
                    q.pop();
                    if(found && dist > distance) continue;//*****이 부분이 없어서 틀림.*****이 부분이 없다면 거리에 1이고 적이 없는 칸이 이 부분을 지나고 거리가 2인곳을 큐에 넣고 난 뒤, 거리가 1인 곳에 적이 발견된다면 큐에 들어간 거리가 2이고 적인 경우도 화살을 맞추게 되서 필요하다.
                    if(map[x][y]==1){//적을 만난 경우.
                        dead[i].push_back(make_pair(y,x));//궁수가 쏠 수 있는 적에 속하므로 벡터에 넣어줌. 가장 왼쪽에 있는 적을 제거하기 위해 y를 먼저 넣음.
                        found=true;
                        distance = dist;
                        continue;
                    }
                    if(found && dist >= distance) continue;//적은 발견됐고 현재 칸에 적이 없고, 거리가 적과의 거리와 같다면 큐에 넣을 필요가 없다.
                    if(dist>=d) continue;
                    for(int i=0; i<3; i++){
                        int nx, ny;
                        nx = x+dx[i];
                        ny = y+dy[i];
                        if(nx<0 || ny<0 || ny>=m) continue;//아래로 내려가는 부분이 필요 없음.
                        if(check[nx][ny]) continue;
                        check[nx][ny] = true;
                        q.emplace(nx,ny,dist+1);
                    }
                }
            }
            set<pair<int,int>> s;//중복 제거 방지.
            for(int i=0; i<3; i++){
                if(dead[i].size()==0) continue;
                sort(dead[i].begin(), dead[i].end());//가장 왼쪽에 있는 적을 제거.
                int x,y;
                tie(y,x) = dead[i][0];
                map[x][y]=0;
                s.insert(make_pair(x,y));
                dead[i].clear();
            }
            enemy += s.size();
            s.clear();
            for(int i=0; i<m; i++)//적 1칸씩 밑으로 전진.
                map[n-1][i] = 0;
            for(int i=n-2; i>=0; i--){
                for(int j=0; j<m; j++){
                    if(map[i][j]==1){
                        map[i][j]=0;
                        map[i+1][j]=1;
                    }
                }
            }
        }
    }
    for(int i=idx; i<m; i++){
        v.push_back(i);
        go(v, i+1);
        v.pop_back();
    }
}

int main(){
    cin >> n >> m >> d;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> a[i][j];
    
    vector<int> v;
    go(v, 0);
    
    cout << ans;
    
    return 0;
}
