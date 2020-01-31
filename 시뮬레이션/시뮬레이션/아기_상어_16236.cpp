//
//  아기_상어_16236.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/01/31.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cstring>
#include <algorithm>

using namespace std;

//먹을 수 있는 물고기 중 거리가 가까운 물고기를 먹는다.
//거리가 가까운 물고기가 여러개라면 가장 위에 있는 물고기, 그러한 물고기가 여러마리라면 가장 왼쪽에 있는 물고기를 먹는다.
//이것이 관건인데 algorithm의 sort 함수를 사용해서 해결했다.
//큐를 이용해서 가장 가까운 물고기중에 먹을 수 있는 물고기를 찾는다.
//이때 found를 사용해서 같은 bfs 단계에서 다른 먹을 수 있는 물고기가 더 있는지 찾도록 했다.

int n;
int a[20][20];//물고기 저장하는 배열.
int d[20][20];//거리 저장하는 배열.
bool check[20][20];//중복 방지 배열.
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};
int ans;

int main(){
    cin >> n;
    int t;
    int sx, sy, size=2, eat=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> a[i][j];
            if(a[i][j]==9){//상어의 위치를 따로 저장한다.
                sx=i;
                sy=j;
                a[i][j]=0;
            }
        }
    }
    queue<pair<int,int>> q;
    vector<pair<int,int>> v;
    q.emplace(sx, sy);//상어의 위치를 큐에 삽입한다.
    check[sx][sy]=true;
    for(t=0; ;t++){
        bool found=false;//하나라도 먹을 수 있는 물고기를 찾았다면 true.
        int distance=0;//그 해당하는 물고기 까지의 거리를 저장.
        while(!q.empty()){
            int x,y;
            tie(x,y) = q.front();
            q.pop();
            if(found)//이미 가까운 거리의 먹을 수 있는 물고기를 찾은 경우.
                if(distance <= d[x][y])//현재 위치가 가까운 물고기 보다 먼 경우.
                    continue;
            
            for(int i=0; i<4; i++){
                int nx, ny;
                nx = x+dx[i];
                ny = y+dy[i];
                if(nx<0 || nx>=n || ny<0 || ny>= n) continue;
                if(check[nx][ny]) continue;
                if(a[nx][ny] > size) continue;//상어보다 큰 물고기는 지나갈 수 없음.
                q.emplace(nx,ny);
                d[nx][ny] = d[x][y]+1;
                check[nx][ny]=true;
                if(a[nx][ny]>0 && a[nx][ny] < size){//상어보다 물고기가 작은 경우.
                    found=true;
                    distance=d[nx][ny];
                    v.push_back(make_pair(nx,ny));//잡을 수 있는 물고기를 벡터에 삽입한다.
                }
            }
        }
        if(!v.size()){//잡을 수 있는 물고기가 벡터에 없는 경우.
            break;
        }
        else{//잡을 수 있는 물고기가 벡터에 있는 경우.
            sort(v.begin(), v.end());
            int nx,ny;
            tie(nx,ny) = v.front();
            a[nx][ny]=0;
            q.emplace(nx,ny);
            eat+=1;
            if(eat>=size){//자신의 크기만큼 물고기를 먹으면 상어의 크기가 1 증가한다.
                size+=1;
                eat=0;
            }
            v.clear();
            ans+=d[nx][ny];
            memset(check, false, sizeof(check));
            memset(d, 0, sizeof(d));
            check[nx][ny]=true;
        }
    }
    
    cout << ans;
    
    return 0;
}
