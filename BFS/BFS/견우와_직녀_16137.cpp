//
//  견우와_직녀_16137.cpp
//  BFS
//
//  Created by jiho park on 2020/01/28.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>
#include <cstring>

using namespace std;

int n, ot;
int map[10][10];
bool check[10][10][10][10];
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int main(){
    cin >> n >> ot;
    memset(map, -1, sizeof(map));
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> map[i][j];
    
    queue<tuple<int,int,int,int,int,int,bool>> q;//현재 위치 x,y. 놓는 오작교 건넌 횟수, 현재 시간, 놓은 오작교의 x,y 위치.
    q.emplace(0,0,0,0,0,0,false);
    check[0][0][0][0] = true;
    while(!q.empty()){
        int x, y, o, t, ox, oy;
        bool p;
        tie(x,y,o,t,ox,oy,p) = q.front();
        q.pop();
        for(int i=0; i<4; i++){
            int nx, ny;
            nx = x+dx[i];
            ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=n) continue;//맵을 벗어난 경우.
            if(check[nx][ny][ox][oy]) continue;//중복 검사.
            if(nx == x && ny == y) continue;//오작교로 올라서 다시 뒤돌아오지 않게 하기 위함. 오작교를 오를 때 중복검사 ox,oy가 바뀌기 때문.
            if(nx==n-1 && ny==n-1){//직녀를 만난 경우.
                cout << t+1;
                return 0;
            }
            if(map[nx][ny]==0 && o==0 && map[nx+dx[i]][ny+dy[i]] != 0 && !p){//건너야 할 곳이 절벽이고, 오작교를 놓을 수 있고, 오작교를 놓아본적이 없고, 절벽이 교차되어있지 않고, 이전에 오작교를 건너지 않은 상태인 경우.
                if((t+1)%ot == 0){//주기가 맞아서 건널 수 있는 경우.
                    q.emplace(nx,ny,o+1,t+1,nx,ny,true);
                    check[nx][ny][nx][ny]=true;
                }
                else//주기가 맞지않으면 기다린다.
                    q.emplace(x,y,o,t+1,ox,oy,p);
                
            }
            else if(map[nx][ny] == 1){//건널 곳이 평지인 경우.
                q.emplace(nx,ny,o,t+1,ox,oy,false);
                check[nx][ny][ox][oy]=true;
            }
            else if(map[nx][ny] > 1 && !p){//이미 놓여져 있는 오작교를 건널 예정이고 이전에 오작교를 건너지 않은 경우.
                if((t+1)%map[nx][ny] == 0){//주기가 맞는 경우.
                    q.emplace(nx,ny,o,t+1,nx,ny, true);
                    check[nx][ny][ox][oy]=true;
                }else{//주기가 맞을 때 까지 기다림.
                    q.emplace(x,y,o,t+1,ox,oy,p);
                }
            }
        }
    }
    
    
    return 0;
}
