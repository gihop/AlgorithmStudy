//
//  main.cpp
//  Retry
//
//  Created by jiho park on 2020/04/05.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>
#include <cstring>

#define endl "\n"
using namespace std;

int a[10][10][10][10];
char map[10][10];
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};
int n,m;
int hx,hy;

tuple<bool,int,int> check_moved(int x, int y, int a, int b, int dirct){
    if(map[x][y]=='O') return make_tuple(false,x,y);
    
    int nx = x+dx[dirct], ny = y+dy[dirct];
    if(map[nx][ny]=='O') return make_tuple(true,nx,ny);
    else if(map[nx][ny]=='.' && (nx!=a || ny!=b)) return make_tuple(true,nx,ny);
    
    return make_tuple(false, x,y);
}

tuple<int,int,int,int> move(int rx, int ry, int bx, int by, int dirct){
    bool red_moved=true, blue_moved=true;
    while(red_moved || blue_moved){
        tie(red_moved, rx, ry) = check_moved(rx, ry, bx, by, dirct);
        tie(blue_moved, bx, by) = check_moved(bx, by, rx, ry, dirct);
    }
    
    return make_tuple(rx, ry, bx, by);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m;
    
    int rx,ry,bx,by;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> map[i][j];
            if(map[i][j]=='B'){
                bx=i;
                by=j;
                map[i][j]='.';
            }else if(map[i][j]=='R'){
                rx=i;
                ry=j;
                map[i][j]='.';
            }else if(map[i][j]=='O'){
                hx=i;
                hy=j;
            }
        }
    }
    
    queue<tuple<int,int,int,int,int>> q;
    q.emplace(rx,ry,bx,by,1);
    a[rx][ry][bx][by]=1;
    int ans=-1;
    bool check = false;
    while(!q.empty()){
        int count;
        tie(rx,ry,bx,by,count) = q.front();
        q.pop();
        if(count>=11) continue;
        for(int i=0; i<4; i++){
            int nrx, nry, nbx, nby;
            tie(nrx,nry,nbx,nby) = move(rx,ry,bx,by,i);
            if(a[nrx][nry][nbx][nby]) continue;
            if(map[nrx][nry]=='O' && map[nbx][nby]!='O'){
                ans = count;
                check=true;
                break;
            }
            if(map[nrx][nry]=='O' || map[nbx][nby]=='O') continue;
            a[nrx][nry][nbx][nby] = count;
            q.emplace(nrx,nry,nbx,nby,count+1);
        }
        if(check) break;
    }
    
    cout << ans;
    
    return 0;
}
