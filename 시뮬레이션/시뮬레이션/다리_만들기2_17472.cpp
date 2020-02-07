//
//  다리_만들기2.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/07.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>
#include <cstdlib>
#include <cstring>

#define endl "\n"
using namespace std;

//문제의 조건이 상당히 까다로운 문제. 그래서 양이 많음.
//자꾸 bfs 할 때 방문 표시를 q에 넣을 때 같이 안하는 실수를 함. 같이 해줘야 함.

int n,m;
int a[10][10];//전체 지도.
bool check[10][10];//전체 지도에서 나라를 찾기 위한 배열.
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};
int conn[6][6];//나라끼리 연결됨을 저장하는 배열.
vector<pair<int,int>> island[6];//각 나라의 위치를 저장하는 벡터.
vector<tuple<int,int,int>> bridge;//놓을 수 있는 모든 다리의 길이와 어느 나라가 연결되는지 저장하는 벡터.
bool check_bridge[15];//어떤 다리를 놓을지 결정하는 배열.
int island_count=1;//나라 수.
bool island_check[10];//모든 나라가 연결되어있는지 확인할 때 필요한 배열.
int ans=9999999;

void go(int idx, int cnt){
    if(cnt>0){
        int sum=0;
        queue<int> q;
        memset(conn, false, sizeof(conn));
        memset(island_check, false, sizeof(island_check));
        for(int i=0; i<bridge.size(); i++){
            if(!check_bridge[i]) continue;//조합에 들어가지 않은 다리인 경우.
            int length, x,y;
            tie(length,x,y) = bridge[i];
            sum+=length;//다리 길이를 미리 더해놓음.
            conn[x][y]=true;//다리 연결.
            conn[y][x]=true;
        }
        
        q.emplace(0);//첫 번째 나라 큐에 삽입.
        int bfs_count=1;//첫 번째 나라를 방문했으니 1 부터 시작. 총 방문 횟수 저장.
        while(!q.empty()){
            int num = q.front();
            q.pop();
            island_check[num]=true;
            for(int i=0; i<island_count; i++){
                if(!conn[num][i]) continue;//두 나라가 연결되어 있지 않은 경우.
                if(island_check[i]) continue;//이미 방문한 나라인 경우.
                island_check[i]=true;//이 부분도 꼭 필요함. 같이 해줘야 함. 이 부분이 없어서 자주 틀림.
                q.emplace(i);
                bfs_count++;//방문 횟수 +1.
            }
        }
        if(island_count==bfs_count && ans > sum)//총 나라의 갯수와 방문 횟수가 같으면 모든 나라가 연결 되어있음을 뜻함.
            ans = sum;
    }
    for(int i=idx; i<bridge.size(); i++){//갯수 1이상의 모든 조합 찾기. 순서가 상관없으니 idx  필요.
        if(check_bridge[i]) continue;
        check_bridge[i]=true;
        go(i, cnt+1);
        check_bridge[i]=false;
    }
}

void possible_bridge(int x, int y){//다리를 놓을 수 있는지 판단.
    int min=10;
    for(int i=0; i<island[x].size(); i++){
        for(int j=0; j<island[y].size(); j++){
            if(island[x][i].first == island[y][j].first){//행이 같은 경우 다리를 놓을 수 있음.
                if(min > abs(island[x][i].second-island[y][j].second)-1 && abs(island[x][i].second-island[y][j].second)-1 > 1){//다리의 길이가 min 보다 작은지 확인하며 다리의 길이가 2이상인지 확인.
                    bool ok=true;
                    if(island[x][i].second > island[y][j].second){
                        for(int k=island[y][j].second+1; k<island[x][i].second; k++){//다리를 놓는 곳 사이에 바다만 있는지 검사하는 부분.
                            if(a[island[x][i].first][k] != 0){
                                ok=false;
                                break;
                            }
                        }
                    }
                    else{
                        for(int k=island[x][i].second+1; k<island[y][j].second; k++){
                            if(a[island[x][i].first][k] != 0){
                                ok=false;
                                break;
                            }
                        }
                    }
                    if(ok)
                        min = abs(island[x][i].second-island[y][j].second)-1;
                }
            }else if(island[x][i].second == island[y][j].second){//열이 같은 경우 다리를 놓을 수 있음.
                if(min > abs(island[x][i].first-island[y][j].first)-1 && abs(island[x][i].first-island[y][j].first)-1 > 1){
                    bool ok=true;
                    if(island[x][i].first > island[y][j].first){
                        for(int k=island[y][j].first+1; k<island[x][i].first; k++){
                            if(a[k][island[x][i].second] != 0){
                                ok=false;
                                break;
                            }
                        }
                    }
                    else{
                        for(int k=island[x][i].first+1; k<island[y][j].first; k++){
                            if(a[k][island[x][i].second] != 0){
                                ok=false;
                                break;
                            }
                        }
                    }
                    if(ok)
                        min = abs(island[x][i].first-island[y][j].first)-1;
                }
            }
        }
    }
    if(min!=10)//다리를 놓을 수 있는 경우.
        bridge.push_back(make_tuple(min, x, y));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> a[i][j];
    
    for(int i=0; i<n; i++){//나라를 구별하고 나라의 총 수와 나라의 지역 좌표를 저장.
        for(int j=0; j<m; j++){
            if(a[i][j]==0 || check[i][j]) continue;//바다이거나 이미 방문한 지역인 경우.
            queue<pair<int,int>> q;
            q.emplace(i,j);
            while(!q.empty()){
                int x,y;
                tie(x,y) = q.front();
                a[x][y]=island_count;
                check[x][y]=true;
                island[island_count-1].push_back(make_pair(x,y));//각 나라의 좌표를 저장.
                q.pop();
                for(int k=0; k<4; k++){
                    int nx,ny;
                    nx = x+dx[k];
                    ny = y+dy[k];
                    if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                    if(check[nx][ny]) continue;
                    if(a[nx][ny]==0) continue;
                    q.emplace(nx,ny);
                    check[nx][ny]=true;
                }
            }
            island_count++;
        }
    }
    island_count-=1;
    if(island_count==1){//나라가 1개면 다리를 놓을 필요가 없음
        cout << 0;
        return 0;
    }

    for(int i=0; i<island_count-1; i++){//각 나라간에 다리를 놓을 수 있는지 검사.
        for(int j=i+1; j<island_count; j++){
            possible_bridge(i, j);
        }
    }
    if(bridge.size()==0){//놓을 수 있는 다리가 0이면 -1.
        cout << -1;
        return 0;
    }
    
    go(0,0);
    
    
    if(ans == 9999999)//다리를 어떻게든 놓아도 모든 나라가 연결되지 않을 경우.
        cout << -1;
    else
        cout << ans;
    
    return 0;
}
