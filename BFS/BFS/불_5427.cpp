//
//  불_5427.cpp
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

//틀렸습니다 떴던 이유 밑에 주석 참고.

int cnt;
int n,m;
char a[1001][1001];
bool fire_check[1001][1001];
bool now_check[1001][1001];
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> cnt;
    for(int k=0; k<cnt; k++){
        cin >> m >> n;
        queue<pair<int,int>> fire, nfire, now, next;
        memset(a, 0, sizeof(a));
        memset(fire_check, false, sizeof(fire_check));
        memset(now_check, false, sizeof(now_check));
        int ax, ay;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                cin >> a[i][j];
                if(a[i][j]=='@'){
                    ax=i;
                    ay=j;
                    now.emplace(i,j);
                    a[i][j]='.';
                    now_check[i][j]=true;
                }else if(a[i][j]=='*'){
                    fire.emplace(i,j);
                    fire_check[i][j]=true;
                }
            }
        }
        for(int ans=0; ;ans++){
            bool exit=false;
            if(now.empty()){
                cout << "IMPOSSIBLE" << endl;
                break;
            }
            while(!fire.empty()){
                int x,y;
                tie(x,y) = fire.front();
                fire.pop();
                for(int l=0; l<4; l++){
                    int nx,ny;
                    nx = x+dx[l];
                    ny = y+dy[l];
                    if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                    if(fire_check[nx][ny]) continue;
                    if(a[nx][ny]=='#') continue;
                    a[nx][ny]='*';
                    nfire.emplace(nx,ny);
                    fire_check[nx][ny]=true;
                }
            }

            while(!now.empty()){
                int x,y;
                tie(x,y) = now.front();
                now.pop();
                for(int l=0; l<4; l++){
                    int nx, ny;
                    nx = x+dx[l];
                    ny = y+dy[l];
                    if(nx<0 || nx>=n || ny<0 || ny>=m){//이 부분 부터 검사해야 하는데 안그러면 맵이 벗어났을 때 a[nx][ny]가 안됨. 그래서 틀렸습니다가 떴음.
                        exit=true;
                        cout << ans+1 << endl;
                        break;
                    }
                    if(a[nx][ny]=='#' || a[nx][ny]=='*') continue;
                    if(now_check[nx][ny]) continue;
                    next.emplace(nx,ny);
                    now_check[nx][ny]=true;
                }
                if(exit) break;
            }
            if(exit) break;
            fire = nfire;
            now = next;
            nfire=queue<pair<int,int>>();
            next=queue<pair<int,int>>();
        }
    }
    
    return 0;
}
