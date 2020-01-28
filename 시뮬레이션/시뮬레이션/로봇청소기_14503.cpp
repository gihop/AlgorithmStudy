//
//  로봇청소기_14503.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/01/28.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

using namespace std;

//로봇청소기_14503 재시도.

int map[50][50];
bool check[50][50];
int n,m;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
int ans=0;

int main(){
    int x,y,dir,cnt=0;
    bool b=false;
    cin >> n >> m;
    cin >> x >> y >> dir;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> map[i][j];
    
    while(true){
        if(!check[x][y] && !b){
            check[x][y]=true;
            ans++;
        }
        int nx, ny;
        nx = x+dx[(dir+3)%4];
        ny = y+dy[(dir+3)%4];
        if(!check[nx][ny] && map[nx][ny]!=1){
            x=nx;
            y=ny;
            dir=(dir+3)%4;
            b=false;
            cnt=0;
            continue;
        }else if(cnt > 3 && map[x+dx[(dir+2)%4]][y+dy[(dir+2)%4]] == 1){
            cout << ans;
            return 0;
        }
        else if(cnt > 3){
            x = x+dx[(dir+2)%4];
            y = y+dy[(dir+2)%4];
            b=true;
            cnt=0;
            continue;
        }
        else{
            dir=(dir+3)%4;
            b=true;
            cnt++;
            continue;
        }
    }
    return 0;
}
