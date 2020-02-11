//
//  통나무_옮기기_1938.cpp
//  BFS
//
//  Created by jiho park on 2020/02/10.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>
#include <set>

#define endl "\n"
using namespace std;

char a[50][50];//전체 맵.
int check[50][50];//정답인지 확인하기 위한 배열.
int n;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    
    int ax, ay, bx, by, cx, cy, cnt=0;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> a[i][j];
            if(a[i][j]=='B'){
                if(cnt==0){
                    ax=i;
                    ay=j;
                    cnt++;
                    a[i][j]='.';
                }else if(cnt==1){
                    bx=i;
                    by=j;
                    cnt++;
                    a[i][j]='.';
                }else{
                    cx=i;
                    cy=j;
                    a[i][j]='.';
                }
            }else if(a[i][j]=='E'){
                check[i][j]=2;
                a[i][j]='.';
            }
        }
    }
    
    queue<tuple<int,int,int,int,int,int,int>> q;
    q.emplace(ax,ay,bx,by,cx,cy,0);
    
    set<tuple<int,int,int,int,int,int>> s;
    s.insert(make_tuple(ax,ay,bx,by,cx,cy));
    
    while(!q.empty()){
        int ax, ay, bx, by, cx, cy, cnt;
        tie(ax, ay, bx, by, cx, cy, cnt) = q.front();
        q.pop();
        if(check[ax][ay]==2 && check[bx][by]==2 && check[cx][cy]==2){//정답인 경우.
            cout << cnt;
            return 0;
        }
        for(int i=0; i<5; i++){
            if(i<4){//단순 이동인 경우.
                int nax, nay, nbx, nby, ncx, ncy;
                nax = ax+dx[i];
                nay = ay+dy[i];
                nbx = bx+dx[i];
                nby = by+dy[i];
                ncx = cx+dx[i];
                ncy = cy+dy[i];
                if(nax<0 || nax>=n || nay<0 || nay>=n || nbx<0 || nbx>=n || nby<0 || nby>=n || ncx<0 || ncx>=n || ncy<0 || ncy>=n) continue;
                if(a[nax][nay]=='1' || a[nbx][nby]=='1' || a[ncx][ncy]=='1') continue;
                if(s.count(make_tuple(nax,nay,nbx,nby,ncx,ncy))>0) continue;
                q.emplace(nax,nay,nbx,nby,ncx,ncy,cnt+1);
                s.insert(make_tuple(nax,nay,nbx,nby,ncx,ncy));
            }else{//회전인 경우.
                int nax,nay,ncx,ncy;
                if(ax == bx){//현재 가로인 경우 -> 세로로 바꿔줌.
                    if(ax<1 || ax>n-2) continue;
                    if(a[ax+1][ay]=='1' || a[ax-1][ay]=='1' || a[bx-1][by]=='1' || a[bx+1][by]=='1' || a[cx-1][cy]=='1' || a[cx+1][cy]=='1') continue;
                    nax=bx-1;
                    nay=by;
                    ncx=bx+1;
                    ncy=by;
                }else{//현재 세로인 경우 -> 가로로 바꿔줌.
                    if(ay<1 || ay>n-2) continue;
                    if(a[ax][ay-1]=='1' || a[ax][ay+1]=='1' || a[bx][by-1]=='1' || a[bx][by+1]=='1' || a[cx][cy-1]=='1' || a[cx][cy+1]=='1') continue;
                    nax=bx;
                    nay=by-1;
                    ncx=bx;
                    ncy=by+1;
                }
                if(s.count(make_tuple(nax,nay,bx,by,ncx,ncy))>0) continue;
                q.emplace(nax,nay,bx,by,ncx,ncy,cnt+1);
                s.insert(make_tuple(nax,nay,bx,by,ncx,ncy));
            }
        }
    }
    
    cout << 0;
    
    return 0;
}
