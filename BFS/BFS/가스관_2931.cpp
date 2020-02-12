//
//  가스관_2931.cpp
//  BFS
//
//  Created by jiho park on 2020/02/11.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>

#define endl "\n"
using namespace std;

//문제를 잘 이해해야 풀 수 있는 문제. 구현하는데 시간이 좀 걸리는 문제임.

int n,m;
char a[25][25];
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};
int ans;//자그레브 까지 이동하는데 걸린 횟수.
int ansx, ansy;//채운 블록의 좌표.
char ansc;//채운 블록의 모양.

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int mx,my,zx=0,zy=0;//모스크바와 자그레브의 좌표.
    
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> a[i][j];
            if(a[i][j]=='M'){
                mx=i;
                my=j;
            }else if(a[i][j]=='Z'){
                zx=i;
                zy=j;
            }
        }
    }
    
    queue<tuple<int,int,int,int,int,char,int>> q; //현재 x,y,현재 방향, 놓은 길 x,y,방향, 움직인 횟수
    q.emplace(mx,my,0,-1,-1,'.',0);
    q.emplace(mx,my,1,-1,-1,'.',0);
    q.emplace(mx,my,2,-1,-1,'.',0);
    q.emplace(mx,my,3,-1,-1,'.',0);
    while(!q.empty()){
        int x,y,dirct,ax,ay,cnt;
        char ad;
        tie(x,y,dirct,ax,ay,ad,cnt) = q.front();
        q.pop();
        
        int nx = x+dx[dirct];
        int ny = y+dy[dirct];
        if(nx<0 || nx>=n || ny<0 || ny>=m) continue;//다음에 가야할 좌표가 맵을 벗어난 경우.
        if(nx==zx && ny==zy && ans < cnt){//다음에 가야할 좌표가 자그레브인 경우, cnt가 더 클때만 들어갈 수 있음. 지워진 블록이 '+'모양 교차점일 경우 두 번 지나야 하는데 한 번만 지난 것이 답이 될 수 있기 때문. 그래서 cnt가 더 크면서 답인 경우가 발생.
            ansx=ax;
            ansy=ay;
            ansc=ad;
            ans=cnt;
        }
        char ch = a[nx][ny];//다음에 가야할 칸의 모양과 현재 방향을 확인하고 들어가야 하기 때문에 저장.
        if(ch == '.' && nx==ax && ny==ay)//지워진 블록이 '+' 모양이면 두 번 들리기 때문임.
            ch=ad;
        if(ch == '|'){
            if(dirct!=3 && dirct!= 1) continue;

            q.emplace(nx,ny,dirct,ax,ay,ad,cnt+1);
        }
        else if(ch == '-'){
            if(dirct!=2 && dirct!= 0) continue;
            
            q.emplace(nx,ny,dirct,ax,ay,ad,cnt+1);
        }
        else if(ch == '+'){
            q.emplace(nx,ny,dirct,ax,ay,ad,cnt+1);
        }
        else if(ch == '1'){
            if(dirct!=3 && dirct!= 2) continue;
            
            if(dirct==3)
                q.emplace(nx,ny,0,ax,ay,ad,cnt+1);
            else
                q.emplace(nx,ny,1,ax,ay,ad,cnt+1);
        }
        else if(ch == '2'){
            if(dirct!=2 && dirct!= 1) continue;
            
            if(dirct==2)
                q.emplace(nx,ny,3,ax,ay,ad,cnt+1);
            else
                q.emplace(nx,ny,0,ax,ay,ad,cnt+1);
        }
        else if(ch == '3'){
            if(dirct!=0 && dirct!= 1) continue;
            
            if(dirct==0)
                q.emplace(nx,ny,3,ax,ay,ad,cnt+1);
            else
                q.emplace(nx,ny,2,ax,ay,ad,cnt+1);
        }
        else if(ch == '4'){
            if(dirct!=3 && dirct!= 0) continue;
            
            if(dirct==3)
                q.emplace(nx,ny,2,ax,ay,ad,cnt+1);
            else
                q.emplace(nx,ny,1,ax,ay,ad,cnt+1);
        }
        else{//다음에 가야할 칸이 빈칸인 경우.
            if(ax!=-1) continue;//이미 채운 블록이 있을 경우.
            else{//아직 채운 블록이 없을 경우 현재 방향에 따라 큐에 삽입.
                if(dirct==0){
                    q.emplace(nx,ny,dirct,nx,ny,'-',cnt+1);
                    q.emplace(nx,ny,dirct,nx,ny,'+',cnt+1);
                    q.emplace(nx,ny,3,nx,ny,'3',cnt+1);
                    q.emplace(nx,ny,1,nx,ny,'4',cnt+1);
                }
                else if(dirct==1){
                    q.emplace(nx,ny,dirct,nx,ny,'|',cnt+1);
                    q.emplace(nx,ny,dirct,nx,ny,'+',cnt+1);
                    q.emplace(nx,ny,0,nx,ny,'2',cnt+1);
                    q.emplace(nx,ny,2,nx,ny,'3',cnt+1);
                }else if(dirct==2){
                    q.emplace(nx,ny,dirct,nx,ny,'-',cnt+1);
                    q.emplace(nx,ny,dirct,nx,ny,'+',cnt+1);
                    q.emplace(nx,ny,1,nx,ny,'1',cnt+1);
                    q.emplace(nx,ny,3,nx,ny,'2',cnt+1);
                }else{
                    q.emplace(nx,ny,dirct,nx,ny,'|',cnt+1);
                    q.emplace(nx,ny,dirct,nx,ny,'+',cnt+1);
                    q.emplace(nx,ny,0,nx,ny,'1',cnt+1);
                    q.emplace(nx,ny,2,nx,ny,'4',cnt+1);
                }
            }
        }
    }
    
    cout << ansx+1 << " " << ansy+1 << " " << ansc;
    
    return 0;
}
