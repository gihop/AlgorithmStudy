//
//  미세먼지_안녕!_17144.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/01/31.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <tuple>

using namespace std;

int a[50][50];
int t;
int n,m;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};
int ans;

tuple<int,int,int> carry(int limit, int nx, int ny, int d, int tmp){//미세먼지를 한 칸 씩 이동시키는 함수.
    int tmp2;
    for(int i=0; i<limit; i++){
        nx += dx[d];
        ny += dy[d];
        tmp2 = a[nx][ny];
        a[nx][ny] = tmp;
        tmp = tmp2;
    }
    return make_tuple(nx, ny, tmp);
}

int main(){
    int ax, ay=0, bx, by=0;//공기청정기 위치.
    cin >> n >> m >> t;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> a[i][j];
            if(a[i][j]==-1){
                bx = i;
            }
        }
    }
    ax = bx-1;
    
    
    for(int time=0; time<t; time++){
        int b[50][50];
        memset(b,0,sizeof(b));
        for(int i=0; i<n; i++){//미세먼지 확산을 b 배열에 저장.
            for(int j=0; j<m; j++){
                if(a[i][j]>0){
                    int cnt=0;
                    for(int k=0; k<4; k++){
                        int nx,ny;
                        nx = i+dx[k];
                        ny = j+dy[k];
                        if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                        if(nx == ax && ny == ay) continue;
                        if(nx == bx && ny == by) continue;
                        b[nx][ny] += a[i][j]/5;
                        cnt++;
                    }
                    a[i][j] = a[i][j] - ((a[i][j]/5)*cnt);
                }
            }
        }
        for(int i=0; i<n; i++)//확산된 미세먼지를 현재 지도에 저장.
            for(int j=0; j<m; j++)
                a[i][j] += b[i][j];

        int nx=ax+dx[0], ny=ay+dx[0];
        int tmp = 0;
        tie(nx,ny,tmp) = carry(m-1, nx, ny, 0, tmp);//미세먼지 반시계방향 전진.
        tie(nx,ny,tmp) = carry(ax, nx, ny, 3, tmp);
        tie(nx,ny,tmp) = carry(m-1, nx, ny, 2, tmp);
        tie(nx,ny,tmp) = carry(ax, nx, ny, 1, tmp);
        a[ax][ay] = -1;//미세먼지 제거.
        
        nx=bx+dx[0];
        ny=ay+dx[0];
        tmp = 0;
        tie(nx,ny,tmp) = carry(m-1, nx, ny, 0, tmp);//미세먼지를 시계방향 전진.
        tie(nx,ny,tmp) = carry(n-bx-1, nx, ny, 1, tmp);
        tie(nx,ny,tmp) = carry(m-1, nx, ny, 2, tmp);
        tie(nx,ny,tmp) = carry(n-bx-1, nx, ny, 3, tmp);
        a[bx][by]=-1;//미세먼지 제거.
    }
    
    for(int i=0; i<n; i++){//총 지도에 미세먼지 더함.
        for(int j=0; j<m; j++){
            if(a[i][j]>0)
                ans += a[i][j];
        }
    }
    
    cout << ans;
    
    return 0;
}
