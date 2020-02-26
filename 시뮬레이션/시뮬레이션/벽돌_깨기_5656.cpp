//
//  벽돌_깨기_5656.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/26.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>
#include <vector>

#define endl "\n"
using namespace std;

//행,렬이 입력되는게 아니라 열,행이 입력순서였다.
//dfs와 bfs를 같이 사용해서 해결했다.
//중복순열을 사용했다. 이 부분은 다시 복습해야 할 것 같다.

int tc;
int n,m,t;
int a[15][12];
int map[15][12];
int position[4];//이 배열에 중복순열(어느 열에 구슬을 쏴서 벽돌을 깰 것 인지)을 넣었다.
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};
int ans=987654321;
int INF=987654321;

bool gravity(int x, int y){//공중에 떠있는 벽돌을 땅으로 내린다.
    bool moved=false;
    for(int i=0; i<n-1; i++){
        if(map[x][y]==0 && map[x-1][y]>0){
            map[x][y]=map[x-1][y];
            map[x-1][y]=0;
            moved=true;//한 번이라도 움직였으면 true를 반환한다.
        }
        x--;
    }
    return moved;
}

void dfs(int cnt){
    if(cnt==t){
        for(int i=0; i<n; i++)//맵을 복사한다.
            for(int j=0; j<m; j++)
                map[i][j] = a[i][j];
        
        for(int i=0; i<cnt; i++){
            int num = position[i];//어느 열의 구슬을 쏠 것인지.
            int x, y;
            y = num;
            x = 0;
            while(true){//행을 증가시키면서 가장 위에 있는 벽돌을 찾거나 맵을 벗어나면 while문 종료.
                if(map[x][y]==0 && x<n) x++;
                else break;
            }
            queue<tuple<int,int,int>> q;
            if(x<n){//x가 맵을 벗어나지 않고 벽돌을 깨트린 경우.
                q.emplace(x,y,map[x][y]);
                map[x][y]=0;//깨진 벽돌은 0으로 표시.
            }
            while(!q.empty()){
                int x,y,length;
                tie(x,y,length) = q.front();
                q.pop();
                for(int j=0; j<4; j++){
                    for(int k=1; k<length; k++){//깨진 벽돌의 숫자-1만큼 상하좌우 주변의 벽돌도 깨트림.
                        int nx, ny;
                        nx = x+dx[j]*k;
                        ny = y+dy[j]*k;
                        if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                        if(map[nx][ny]==0) continue;
                        if(map[nx][ny]>1)//1은 주변 벽돌을 부수지 못해서 넣지 않고, 1보다 큰 숫자의 벽돌은 큐에 넣는다.
                            q.emplace(nx,ny,map[nx][ny]);
                        map[nx][ny]=0;
                    }
                }
            }
            for(int j=0; j<m; j++)//모든 열을 차례로 공중에 떠있는 벽돌이 없는지 검사.
                while(true)//벽돌이 공중에 아무도 떠있지 않을 때 까지 한 열을 검사.
                    if(!gravity(n-1, j)) break;
        }
        int count=0;
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                if(map[i][j]>0) count++;//깨지지 않은 벽돌 수 검사.
        
        if(ans > count)
            ans=count;
        return;
    }
    for(int i=0; i<m; i++){//중복 순열.
        position[cnt]=i;
        dfs(cnt+1);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> tc;
    for(int i=0; i<tc; i++){
        cin >> t >> m >> n;
        for(int j=0; j<n; j++){
            for(int k=0; k<m; k++){
                cin >> a[j][k];
            }
        }
        dfs(0);
        cout << "#" << i+1 << " " << ans << endl;
        ans = INF;
    }
    
    return 0;
}
