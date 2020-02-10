//
//  다리_만들기_2146.cpp
//  BFS
//
//  Created by jiho park on 2020/02/10.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>
#include <cstring>

#define endl "\n"
using namespace std;

//bfs로 풀이.

int a[100][100];
bool check[100][100];
int d[100][100];
int n;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};
int ans=1000;//100넣었다가 계속 틀렸습니다가 떴었다. 넉넉하게 잡아야한다. 100이 아닌 최대 200까지도 가능하기 때문.

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> a[i][j];
    
    int num=1;
    for(int i=0; i<n; i++){//각 섬에 라벨링을 함.
        for(int j=0; j<n; j++){
            if(a[i][j]>0 && !check[i][j]){
                queue<pair<int,int>> q;
                check[i][j]=true;
                q.emplace(i,j);
                a[i][j]=num;
                while(!q.empty()){
                    int x,y;
                    tie(x,y) = q.front();
                    q.pop();
                    for(int k=0; k<4; k++){
                        int nx, ny;
                        nx = x+dx[k];
                        ny = y+dy[k];
                        if(nx<0 || nx>=n || ny<0 || ny>=n) continue;
                        if(check[nx][ny]) continue;
                        if(a[nx][ny]==0) continue;
                        a[nx][ny]=num;
                        check[nx][ny]=true;
                        q.emplace(nx,ny);
                    }
                }
                num++;
            }
        }
    }
    
    for(int i=0; i<n; i++){//각 칸에서 다른 섬으로 갈 수 있는 최단거리를 구함.
        for(int j=0; j<n; j++){
            if(a[i][j]>0){
                memset(d, 0, sizeof(d));
                queue<pair<int,int>> q;
                q.emplace(i,j);
                d[i][j]=1;
                bool found=false;
                int num = a[i][j];
                while(!q.empty()){
                    int x,y;
                    tie(x,y) = q.front();
                    q.pop();
                    for(int k=0; k<4; k++){
                        int nx, ny;
                        nx = x+dx[k];
                        ny = y+dy[k];
                        if(nx<0 || nx>= n || ny<0 || ny>=n) continue;
                        if(d[nx][ny]>0) continue;
                        if(a[nx][ny]==num) continue;
                        if(a[nx][ny]==0){
                            q.emplace(nx,ny);
                            d[nx][ny] = d[x][y]+1;
                        }
                        else if(a[nx][ny]>0){
                            found=true;
                            if(ans > d[x][y])
                                ans=d[x][y];
                            break;
                        }
                    }
                    if(found)
                        break;
                }
            }
        }
    }
    cout << ans-1;
    
    return 0;
}
