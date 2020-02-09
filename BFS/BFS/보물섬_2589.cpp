//
//  보물섬_2589.cpp
//  BFS
//
//  Created by jiho park on 2020/02/09.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>
#include <cstring>

#define endl "\n"
using namespace std;

int n,m;
char a[50][50];
int d[50][50];
int Max;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> a[i][j];
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(a[i][j]=='L'){
                queue<pair<int,int>> q;
                memset(d, false, sizeof(d));
                q.emplace(i,j);
                d[i][j]=1;
                while(!q.empty()){
                    int x,y;
                    tie(x,y)=q.front();
                    q.pop();
                    for(int k=0; k<4; k++){
                        int nx,ny;
                        nx = x+dx[k];
                        ny = y+dy[k];
                        if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                        if(d[nx][ny]>0) continue;
                        if(a[nx][ny]=='W') continue;
                        q.emplace(nx,ny);
                        d[nx][ny] = d[x][y]+1;
                        if(Max < d[nx][ny])//도달한 거리가 Max보다 큰 경우.
                            Max = d[nx][ny];
                    }
                }
            }
        }
    }
    
    cout << Max-1;//1로 시작하기 때문.
    
    return 0;
}
