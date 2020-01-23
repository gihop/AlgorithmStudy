//
//  과외맨_5213.cpp
//  BFS
//
//  Created by jiho park on 2020/01/23.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <stack>
#include <tuple>//tie 함수 쓰려면 tuple 필요함.

using namespace std;

int map[500][500][2];//입력된 맵.
bool check[500][500];//중복 정점 검사 배열.
int dist[500][500];//거리 저장 배열.
pair<int,int> from[500][500];//답에 경로를 순서대로 출력하기 위한 배열.
int dx0[] = {0, 1, 1, 0, -1, -1};
int dy0[] = {1, 0, -1, -1, -1, 0};
int dx1[] = {0, 1, 1, 0, -1, -1};
int dy1[] = {1, 1, 0, -1, 0, 1};

bool ok(int x, int y, int n){//x,y가 입력된 배열에 있는지 검사.
    if(x<0 || x>=n || y<0 || y>=n) return false;
    if(x%2==1 && y >= n-1) return false;
    else return true;
}

bool go(int x1, int y1, int x2, int y2){//인접한 타일이 같은 숫자인지 검사.
    if(x1 == x2){
        if(y1 > y2){
            if(map[x1][y1][0] == map[x2][y2][1])
                return true;
        }else{
            if(map[x1][y1][1] == map[x2][y2][0])
                return true;
        }
    }else{
        if(x1%2==0){
            if(y1 == y2){
                if(map[x1][y1][1] == map[x2][y2][0])
                    return true;
            }else{
                if(map[x1][y1][0] == map[x2][y2][1])
                    return true;
            }
        }else{
            if(y1 < y2){
                if(map[x1][y1][1] == map[x2][y2][0])
                    return true;
            }else{
                if(map[x1][y1][0] == map[x2][y2][1])
                    return true;
            }
        }
    }
    
    return false;
}

int num(int x, int y, int n){//x,y로 몇 번째 타일인지 계산.
    int num = x/2*(2*n-1);
    if(x%2==1)
        num+=n;
    num+=y+1;
    
    return num;
}

int main(){
    int n;
    
    cin >> n;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n-1; j++){
            cin >> map[i][j][0];
            cin >> map[i][j][1];
        }
        if(i%2==0){
            cin >> map[i][n-1][0];
            cin >> map[i][n-1][1];
        }
    }
    
    check[0][0]=true;//첫 번째 정점 방문.
    dist[0][0]=1;//첫 번째 정점은 거리 1.
    queue<pair<int,int>> q;
    q.emplace(0,0);//첫 번째 정점 큐에 삽입.
    
    while(!q.empty()){
        int x,y;
        tie(x,y) = q.front();
        q.pop();
        for(int i=0; i<6; i++){
            int nx=x, ny=y;
            if(nx%2==0){
                nx+=dx0[i];
                ny+=dy0[i];
            }else{
                nx+=dx1[i];
                ny+=dy1[i];
            }
            if(!ok(nx, ny, n)) continue;//갈 수 없는 배열인 경우.
            if(!go(x, y, nx, ny)) continue;//인접한 타일이 같은 숫자가 아닌 경우.
            if(check[nx][ny]) continue;//이미 방문한 정점인 경우.
            check[nx][ny]=true;//새로운 정점 방문.
            dist[nx][ny] = dist[x][y]+1;//이전 정점에서의 거리에 +1로 거리 저장.
            from[nx][ny] = make_pair(x,y);//이전 정점의 위치를 저장.
            q.emplace(nx, ny);//새로운 정점 큐에 삽입.
        }
    }
    
    int x=n-1, y=n-1;
    while(!check[x][y]){//문제에 따르면 마지막 타일에 갈 수 없으면 가장 번호가 큰 타일로 이동해야 함.
        y-=1;
        if(y<0){
            x-=1;
            if(x%2==0)
                y=n-1;
            else
                y=n-2;
        }
    }
    
    cout << dist[x][y] << endl;//도달할 수 있는 마지막 타일의 거리 출력.
    stack<pair<int,int>> s;
    while(x!=0 || y!=0){//순서대로 출력하기 위해 from 변수를 따라서 시작점까지 이동하며 스택에 저장.
        s.push(make_pair(x,y));
        tie(x,y) = from[x][y];
    }
    s.push(make_pair(0,0));
    
    while(!s.empty()){
        tie(x,y) = s.top();
        s.pop();
        cout << num(x,y,n) << " ";
    }
    
    return 0;
}
