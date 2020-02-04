//
//  파이프_옮기기1_17070.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/04.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>

using namespace std;

int n;
int a[16][16];
int dx1[3][3]={//0번은 누운 모양, 1번은 대각선 모양, 2번은 세운 모양. 각 배열 원소는 어떤 모양일 때 이렇게 움직임을 뜻한다. dx1[1][2]는 파이프의 첫 번째 칸이 모양이 대각선 모양일 때 세운 모양으로 움직일 때의 인덱스 변화를 나타낸다.
    {0, 0},
    {1, 1, 1},
    {0, 1, 1}
};
int dy1[3][3]={
    {1, 1},
    {1, 1, 1},
    {0, 0, 0}
};
int dx2[3][3]={
    {0, 1},
    {0, 1, 1},
    {0, 1, 1}
};
int dy2[3][3]={
    {1, 1},
    {1, 1, 0},
    {0, 1, 0}
};
int ans;

int main(){
    cin >> n;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> a[i][j];
    
    queue<tuple<int,int,int,int,int>> q;
    q.emplace(0,0,0,1,0);//처음엔 첫 번째칸 0,0 두 번째칸 0,1 모양은 누운 모양으로 시작한다.
    
    while(!q.empty()){
        int x1,y1,x2,y2,shape;
        tie(x1,y1,x2,y2,shape) = q.front();
        if(x2 == n-1 && y2 == n-1) ans++;//맵의 끝에 도달하면 ans+1.
        q.pop();
        if(shape==0){//누운 모양일 때.
            for(int i=0; i<2; i++){
                int nx1, nx2, ny1, ny2;
                nx1 = x1+dx1[0][i];
                ny1 = y1+dy1[0][i];
                nx2 = x2+dx2[0][i];
                ny2 = y2+dy2[0][i];
                if(nx2 >= n || ny2 >= n) continue;//맵에서 벗어나는 경우.
                if(i==0 && a[nx2][ny2] == 1) continue;//벽을 만난 경우.
                if(i==1 && (a[nx2][ny2]==1 || a[nx2-1][ny2]==1 || a[nx2][ny2-1]==1))//벽을 만난 경우.
                    continue;
                q.emplace(nx1, ny1, nx2, ny2, i);
            }
        }else if(shape==1){//대각선 모양일 때.
            for(int i=0; i<3; i++){
                int nx1, nx2, ny1, ny2;
                nx1 = x1+dx1[1][i];
                ny1 = y1+dy1[1][i];
                nx2 = x2+dx2[1][i];
                ny2 = y2+dy2[1][i];
                if(nx2 >= n || ny2 >= n) continue;
                if((i==0 || i==2) && a[nx2][ny2] == 1) continue;
                if(i==1 && (a[nx2][ny2]==1 || a[nx2-1][ny2]==1 || a[nx2][ny2-1]==1)) continue;
                q.emplace(nx1, ny1, nx2, ny2, i);
            }
        }else{//세운 모양일 때.
            for(int i=1; i<3; i++){
                int nx1, nx2, ny1, ny2;
                nx1 = x1+dx1[2][i];
                ny1 = y1+dy1[2][i];
                nx2 = x2+dx2[2][i];
                ny2 = y2+dy2[2][i];
                if(nx2 >= n || ny2 >= n) continue;
                if(i==2 && a[nx2][ny2] == 1) continue;
                if(i==1 && (a[nx2][ny2]==1 || a[nx2-1][ny2]==1 || a[nx2][ny2-1]==1)) continue;
                q.emplace(nx1, ny1, nx2, ny2, i);
            }
        }
    }
    
    cout << ans;
    
    return 0;
}
