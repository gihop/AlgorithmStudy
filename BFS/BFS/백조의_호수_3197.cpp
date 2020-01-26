//
//  백조의_호수_3197.cpp
//  BFS
//
//  Created by jiho park on 2020/01/26.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <cstring>

using namespace std;

char a[1500][1500];
bool scheck[1500][1500];
bool wcheck[1500][1500];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int main(){
    int n, m;
    
    cin >> n >> m;
    
    int lx, ly, lx2, ly2;
    lx=ly=lx2=ly2=-1;
    
    queue<pair<int,int>> water, nwater, swan, nswan;//water는 현재 물을 나타내고, nwater는 물에 인접한 얼음들 즉 다음턴에 물이될 얼음들을 저장. swan은 백조가 갈 수 있는 범위를 나타내고 nswan은 백조가 얼음에 갔을 때 즉 다음턴에 이 얼음이 물이되서 백조가 갈 수 있게 된 곳을 의미함.
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> a[i][j];
            if(a[i][j] == 'L'){
                if(lx==-1){//첫 번째 백조 위치 저장.
                    lx = i;
                    ly = j;
                    
                }else{//두 번째 백조 위치 저장.
                    lx2 = i;
                    ly2 = j;
                }
                a[i][j] = '.';//백조는 물로 바꿔놓음.
            }
            if(a[i][j] == '.')
                water.emplace(i,j);//초기 물의 위치 저장.
        }
    }
    
    swan.emplace(lx,ly);//백조의 위치 큐에 저장.
    scheck[lx][ly]=true;//방문 저장.
    
    for(int ans=0; ;ans++){
        while(!water.empty()){//처음 실행될 때는 다음에 물이 될 얼음들을 큐에 저장함. 그 다음부터는 물이 될 얼음들을 물로 바꿔주고 그 다음에 물이 될 얼음들을 큐에 저장함.
            int x,y;
            tie(x,y) = water.front();
            water.pop();
            a[x][y]='.';
            for(int k=0; k<4; k++){
                int nx, ny;
                nx = x+dx[k];
                ny = y+dy[k];
                if(nx<0 || nx>= n || ny<0 || ny>=m) continue;
                if(wcheck[nx][ny]) continue;
                if(a[nx][ny]=='X'){//다음에 물이 될 얼음들.
                    nwater.emplace(nx,ny);
                    wcheck[nx][ny]=true;
                }else{
//                    water.emplace(nx,ny); //다시 큐에 안넣어도 됨. 처음에 입력 받을 때 이미 얼음을 저장하기 때문.
                    wcheck[nx][ny]=true;
                }
            }
        }
        
        while(!swan.empty()){//백조가 갈 수 있는 범위를 계속 넓힘. 다음에 갈 수 있게 될 곳을 큐에 저장함.
            int x, y;
            tie(x,y) = swan.front();
            swan.pop();
            for(int i=0; i<4; i++){
                int nx, ny;
                nx = x+dx[i];
                ny = y+dy[i];
                if(nx<0 || nx>= n || ny<0 || ny>=m) continue;
                if(scheck[nx][ny]) continue;
                if(a[nx][ny] == 'X') {//다음 턴에 갈 수 있게 될 곳.
                    nswan.emplace(nx,ny);
                    scheck[nx][ny]=true;
                }else{
                    swan.emplace(nx,ny);
                    scheck[nx][ny]=true;
                }
            }
        }
        if(scheck[lx2][ly2]){//두 번째 백조가 방문이 될 경우.
            cout << ans;
            break;
        }
        water = nwater;//다음에 가야할 곳 들을 현재 저장된 곳으로 바꿈.
        swan = nswan;
        nwater = queue<pair<int,int>>();//이미 있던 큐 초기화해서 재사용하는 방법.
        nswan = queue<pair<int,int>>();
        
    }
    
    return 0;
}
