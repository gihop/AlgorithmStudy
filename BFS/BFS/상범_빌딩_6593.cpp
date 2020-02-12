//
//  상범_빌딩_6593.cpp
//  BFS
//
//  Created by jiho park on 2020/02/12.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>
#include <cstring>

#define endl "\n"
using namespace std;

//문제 쉽다고 대충 풀지말자.
//틀린 이유 밑에 주석 씀.

char a[30][30][30];
int d[30][30][30];
int l,n,m;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int sl,sx,sy, el,ex,ey;
    while(true){
        memset(d, 0, sizeof(d));//잘 생각해보면 같은 크기의 지도, 시작 위치 끝 위치가 같은 두 지도가 들어왔을 때 먼저 입력된 지도에서는 탈출에 성공하고 그 다음 지도에서는 실패했다면 d는 초기화 되어야 한다. 틀린 이유 밑에 또 있다.
        cin >> l >> n >> m;
        if(l==0 && n==0 && m==0)
            break;
        for(int i=0; i<l; i++){
            for(int j=0; j<n; j++){
                for(int k=0; k<m; k++){
                    cin >> a[i][j][k];
                    if(a[i][j][k]=='S'){
                        sl=i;
                        sx=j;
                        sy=k;
                    }else if(a[i][j][k]=='E'){
                        el=i;
                        ex=j;
                        ey=k;
                    }
                }
            }
        }
        
        queue<tuple<int,int,int>> q;
        q.emplace(sl,sx,sy);
        d[sl][sx][sy]=1;
        
        while(!q.empty()){
            int z,x,y;
            tie(z,x,y)=q.front();
            q.pop();
            if(z==el && x==ex && y==ey)
                break;
            
            for(int i=0; i<6; i++){
                int nx, ny;
                if(i<4){
                    nx = x+dx[i];
                    ny = y+dy[i];
                    if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                    if(d[z][nx][ny]>0) continue;
                    if(a[z][nx][ny]=='#') continue;
                    d[z][nx][ny]= d[z][x][y]+1;
                    q.emplace(z,nx,ny);
                }else if(i==4){
                    int nl=z+1;
                    if(nl>=l) continue;
                    if(d[nl][x][y]>0) continue;
                    if(a[nl][x][y]=='#') continue;
                    d[nl][x][y] = d[z][x][y]+1;
                    q.emplace(nl,x,y);
                }else{
                    int nl=z-1;
                    if(nl<0) continue;
                    if(d[nl][x][y]>0) continue;
                    if(a[nl][x][y]=='#') continue;
                    d[nl][x][y] = d[z][x][y]+1;
                    q.emplace(nl,x,y);
                }
            }
        }
        if(d[el][ex][ey]>0)
            cout << "Escaped in " << d[el][ex][ey]-1 << " minute(s)." << endl;
        else
            cout << "Trapped!" << endl;
        q=queue<tuple<int,int,int>>();//이 부분 역시 큐가 다 비워지기 전에 탈출구를 찾으면 break되므로 큐를 다시 비워줘야 한다.
    }
    
    return 0;
}
