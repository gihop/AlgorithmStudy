//
//  탈출_3055.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/08.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

#define endl "\n"
using namespace std;

char a[50][50];//전체 맵.
bool water_check[50][50];//물 중복 제거.
bool now_check[50][50];//고슴도치 중복 제거.
int d[50][50];
int n,m;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    
    int sx, sy, ax, ay;
    
    queue<pair<int,int>> water, nwater, now, nnow;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> a[i][j];
            if(a[i][j]=='D'){//비버의 소굴일 경우.
                ax=i;
                ay=j;
            }else if(a[i][j]=='S'){//고슴도치일 경우.
                sx=i;
                sy=j;
                a[i][j]='.';
                now.push(make_pair(i, j));
                now_check[i][j]=true;
                d[i][j]=1;
            }else if(a[i][j]=='*'){//물인 경우.
                water.push(make_pair(i, j));
                water_check[i][j]=true;
            }
        }
    }
    
    while(true){
        if(now.empty())//고슴도치가 갈 곳이 없을 경우.
            break;
        while(!water.empty()){//물이 퍼짐.
            int x,y;
            tie(x,y) = water.front();
            water.pop();
            for(int i=0; i<4; i++){
                int nx, ny;
                nx = x+dx[i];
                ny = y+dy[i];
                if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                if(water_check[nx][ny]) continue;
                if(a[nx][ny]=='X' || a[nx][ny]=='D' || a[nx][ny]=='*') continue;//돌, 비버의 소굴, 이미 물인 경우.
                a[nx][ny]='*';//다음에 물이 퍼질 곳을 고슴도치가 못가게 함.
                nwater.emplace(nx,ny);//다음에 물이 퍼질 곳을 저장.
                water_check[nx][ny]=true;
            }
        }

        while(!now.empty()){
            int x,y;
            tie(x,y) = now.front();
            now.pop();
            for(int i=0; i<4; i++){
                int nx, ny;
                nx = x+dx[i];
                ny = y+dy[i];
                if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                if(now_check[nx][ny]) continue;
                if(a[nx][ny]=='X' || a[nx][ny]=='*') continue;//돌, 물인 경우.
                nnow.emplace(nx,ny);
                now_check[nx][ny]=true;
                d[nx][ny] = d[x][y]+1;
            }
        }
        if(now_check[ax][ay]){//고슴도치가 비버의 소굴에 도착한 경우.
            cout << d[ax][ay]-1;
            return 0;
        }
        
        water=nwater;
        now=nnow;
        nwater = queue<pair<int,int>>();//다음에 물이 될 곳과 다음에 비버가 간 곳을 초기화.
        nnow = queue<pair<int,int>>();
    }
    
    cout << "KAKTUS";//고슴도치가 비버의 소굴에 도착하지 못했을 경우.
    
    return 0;
}
