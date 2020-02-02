//
//  연구소3_17142.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/01.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

//문제의 요구에 맞추려면 d배열을 0으로 초기화하는 것이 아니라 -1로 초기화를 했어야 했음.

int a[50][50];
int d[50][50];//바이러스를 전파하는데 걸리는 시간을 저장함. 활성바이러스가 비활성 바이러스를 만났을 때는 주변의 빈 공간에 걸린 시간을 저장한 후에 활성바이러스가 갖고 있는 걸린 시간으로 다시 저장해야함.
int n, m;
vector<pair<int,int>> v;//맵에 있는 모든 바이러스 위치를 담고 있음.
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};
int ans=100000;

void go(queue<tuple<int,int,bool,int>> q){
    while(!q.empty()){
        int x,y,pre;
        bool virus;
        tie(x,y,virus,pre) = q.front();
        q.pop();
        for(int i=0; i<4; i++){
            int nx, ny;
            nx = x+dx[i];
            ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=n) continue;
            if(d[nx][ny]>=0) continue;//이미 바이러스에 감염된 경우.
            if(a[nx][ny] == 1){//벽을 만난 경우.
                d[nx][ny]=1;
                continue;
            }
            if(a[nx][ny]==0){//빈칸을 만난 경우.
                d[nx][ny] = d[x][y]+1;
                q.emplace(nx,ny,false,0);
            }
            else if(a[nx][ny]==2){//비활성 바이러스를 만난 경우.
                d[nx][ny] = d[x][y]+1;
                q.emplace(nx,ny,true,pre);
            }
        }
        if(virus)//내가 비활성 바이러스인 경우.
            d[x][y]=pre;
    }
}

void select(int cnt, int idx, vector<pair<int,int>> v2){
    if(cnt==m){//놓을 수 있는 활성 바이러스를 모두 놓은 경우.
        queue<tuple<int,int,bool,int>> q;//활성 바이러스의 위치, 비활성 바이러스 여부와 비활성 바이러스를 전파할 때의 시간.
        for(int i=0; i<v2.size(); i++){
            int x,y;
            tie(x,y) = v2[i];
            q.emplace(x,y,false,0);
            d[x][y]=0;//초기 활성바이러스의 시작값은 0.
        }
        go(q);
        
        int max=0;
        bool check=false;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(d[i][j]==-1 && a[i][j]!=1)//바이러스가 도달 못하면서 벽이 아닌 경우.
                    check=true;
                if(d[i][j]>max)
                    max = d[i][j];
                d[i][j]=-1;
            }
        }
        if(max < ans && !check)//맵안의 최댓값이 최소 걸린시간보다 적고 바이러스가 도달 못한 빈칸이 없는 경우.
            ans = max;
        
        return;
    }
    for(int i=idx+1; i<v.size(); i++){
        int x,y;
        tie(x,y) = v[i];
        v2.push_back(make_pair(x,y));
        select(cnt+1,i,v2);
        v2.pop_back();
    }
}

int main(){
    cin >> n >> m;
    bool check=false;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> a[i][j];
            if(a[i][j]==2)
                v.push_back(make_pair(i,j));//모든 바이러스 위치를 담을 벡터.
            if(a[i][j]==0)
                check = true;
        }
    }
    if(!check){
        cout << 0;
        return 0;
    }
    memset(d, -1, sizeof(d));
    vector<pair<int,int>> v2;//활성 바이러스 위치를 담을 벡터.
    select(0, -1, v2);
    
    if(ans == 100000)
        cout << -1;
    else
        cout << ans;
    
    return 0;
}
