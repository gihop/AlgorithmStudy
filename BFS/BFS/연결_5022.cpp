//
//  연결_5022.cpp
//  BFS
//
//  Created by jiho park on 2020/02/15.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>
#include <vector>
#include <cstring>

#define endl "\n"
using namespace std;

//처음에 이 문제를 풀 때 좌표에 모두 2를 곱해야 한다고 생각했었는데 그럴필요 없이 전체 배열 값에 1씩 더해주면 됐다.
//문제를 보면 6x6 배열에 있을 수 있는 좌표가 (6,6)이기 때문에 사실상 7x7배열로 하면 된다.
//따라서 배열 전체칸은 101x101이다.
//한 쪽을 최단거리로 연결하고 다른쪽을 연결 시킬 수 있는지를 봐야하는데 최단거리로 연결할 때 어떤 모양으로 연결하든지 상관없다.
//최단거리로 연결할 때 어느 모양인지에 따라 결과가 다르다고 생각했었는데 그렇지 않고 한 최단거리가 다른 최단거리 경로를 모두 포함하게 된다.
//한 쪽을 최단거리로 연결했을 때 다른 쪽을 연결할 때 최단거리 경로를 피해서 연결을 해야하는데 그러면 최단거리로 찾은 경로를 저장할 필요가 있었다.
//이 부분을 어떻게 구현할지가 관건이였는데 큐에 벡터를 넣어서 자기가 이동한 좌표를 모두 벡터에 담아서 큐에 다시 넣는 방식으로 해결할 수 있었다.
//또한 빨간줄을 먼저 최단거리로 연결해야하는지 파란줄을 먼저 최단거리로 연결해야하는지 알 수가 없다.
//그래서 양쪽 다 해보고 둘의 총 경로값을 비교해야 한다.

bool visit[101][101];
bool check[101][101];
int n,m;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> m >> n;//n,m 순서로 입력을 받아서 틀렸었다. 문제를 잘 보자.
    n+=1;//1씩 더해줘야 한다.
    m+=1;
    int a1x, a1y, a2x, a2y, b1x, b1y, b2x, b2y;
    cin >> a1y >> a1x;
    cin >> a2y >> a2x;
    cin >> b1y >> b1x;
    cin >> b2y >> b2x;
    
    //빨간줄 먼저 최단거리를 찾는다.
    queue<tuple<int,int,int,vector<pair<int,int>>>> q;//현재 좌표, 총 거리 값, 벡터에는 여태 지나온 모든 좌표가 저장된다.
    vector<pair<int,int>> tmp;//처음에 시작할 때는 빈 벡터로 시작한다.
    q.emplace(a1x, a1y,0,tmp);
    check[a1x][a1y]=true;
    bool found=false;
    int max_red=0;
    while(!q.empty()){
        int x, y, d;
        vector<pair<int,int>> v;
        tie(x,y,d,v) = q.front();
        q.pop();
        if(x == a2x && y == a2y){//두 번째 빨간점 좌표에 도달한 경우.
            found=true;
            max_red=d;
            v.push_back(make_pair(x,y));//두 번째 빨간점 좌표를 벡터에 마지막으로 넣는다.
            for(int i=0; i<v.size(); i++){//여태 지나온 경로에 대한 좌표를 모두 방문 표시 해준다. 다음 파란점을 연결할 때 이 좌표들을 피하기 위함이다.
                int rx, ry;
                tie(rx, ry) = v[i];
                visit[rx][ry]=true;
            }
            continue;
        }
        if(found && d >= max_red) continue;//한 번 최단경로를 찾고난 뒤에 최단경로가 아닌 경로들은 모두 이곳에서 탐색을 멈춘다.
        for(int i=0; i<4; i++){
            int nx, ny;
            nx = x+dx[i];
            ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
            if(check[nx][ny]) continue;
            if((nx == b1x && ny == b1y)||(nx == b2x && ny == b2y)) continue;//최단 경로를 찾을 때 파란점은 피해야한다.
            v.push_back(make_pair(x,y));
            q.emplace(nx,ny,d+1,v);
            check[nx][ny]=true;
        }
    }

    queue<tuple<int,int,int>> q2;//파란점을 이어줄 큐. 최단경로의 모든 좌표값을 필요로 하는 빨간점 큐와는 달리 벡터가 필요하지 않다. 경로를 알필요가 없다. 연결되는지만 확인하면 된다.
    q2.emplace(b1x,b1y,0);
    check[b1x][b1y]=true;
    int max_blue=0;
    found = false;
    memset(check, false, sizeof(check));
    while(!q2.empty()){
        int x, y, d;
        tie(x,y,d) = q2.front();
        q2.pop();
        if(x == b2x && y == b2y){//두 번째 파란점을 찾은 경우.
            found=true;
            max_blue=d;
            continue;
        }
        if(found && d >= max_blue) continue;
        for(int i=0; i<4; i++){
            int nx, ny;
            nx = x+dx[i];
            ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
            if(check[nx][ny]) continue;
            if(visit[nx][ny]) continue;//빨간점 최단거리 경로를 피해야 한다.
            q2.emplace(nx,ny,d+1);
            check[nx][ny]=true;
        }
    }
    
    int ans=0;
    if(max_blue!=0)//파란점을 연결하지 못했을 경우 탐색은 실패한 것.
        ans=max_red+max_blue;
    
    //이번에는 반대로 파란점을 먼저 최단거리를 찾고 빨간점을 연결한다.
    memset(check, false, sizeof(check));
    memset(visit, false, sizeof(visit));
    q.emplace(b1x, b1y,0,tmp);
    check[b1x][b1y]=true;
    found=false;
    max_blue=0;
    while(!q.empty()){
        int x, y, d;
        vector<pair<int,int>> v;
        tie(x,y,d,v) = q.front();
        q.pop();
        if(x == b2x && y == b2y){
            found=true;
            max_blue=d;
            v.push_back(make_pair(x,y));
            for(int i=0; i<v.size(); i++){
                int rx, ry;
                tie(rx, ry) = v[i];
                visit[rx][ry]=true;
            }
            continue;
        }
        if(found && d >= max_blue) continue;
        for(int i=0; i<4; i++){
            int nx, ny;
            nx = x+dx[i];
            ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
            if(check[nx][ny]) continue;
            if((nx == a1x && ny == a1y)||(nx == a2x && ny == a2y)) continue;
            v.push_back(make_pair(x,y));
            q.emplace(nx,ny,d+1,v);
            check[nx][ny]=true;
        }
    }
    q2.emplace(a1x,a1y,0);
    check[a1x][a1y]=true;
    max_red=0;
    found = false;
    memset(check, false, sizeof(check));
    while(!q2.empty()){
        int x, y, d;
        tie(x,y,d) = q2.front();
        q2.pop();
        if(x == a2x && y == a2y){
            found=true;
            max_red=d;
            continue;
        }
        if(found && d >= max_red) continue;
        for(int i=0; i<4; i++){
            int nx, ny;
            nx = x+dx[i];
            ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
            if(check[nx][ny]) continue;
            if(visit[nx][ny]) continue;
            q2.emplace(nx,ny,d+1);
            check[nx][ny]=true;
        }
    }
    int ans2=0;
    if(max_red!=0)
        ans2 = max_blue+max_red;
    
    if(ans==0 && ans2==0)
        cout << "IMPOSSIBLE";
    else if(ans==0)
        cout << ans2;
    else if(ans2==0)
        cout << ans;
    else if(ans>ans2)
        cout << ans2;
    else if(ans<=ans2)
        cout << ans;
    
    return 0;
}
