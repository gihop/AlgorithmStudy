//
//  로봇_조종하기_2169.cpp
//  DP
//
//  Created by jiho park on 2020/03/12.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <algorithm>

#define endl "\n"
using namespace std;

//dp에 값을 비교하고 저장하면서 dfs를 했을 때 시간초과가 발생함.

int n,m;
int a[1000][1000];
int dp[1000][1000][3];//한 원소를 어떤 방향으로 도달했는지에 따라서 가치의 합 최댓값이 달라질 수 있어서 dp[x][y][dirct]는 x,y에 dirct 방향으로 도달했을 때 최댓값을 의미한다. 음의 최댓값(INF)으로 초기화를 해야한다.
bool check[1000][1000];
int dx[]={0, 1, 0};
int dy[]={1, 0, -1};
int INF = -987654321;//음의 최댓값.

int go(int x, int y, int dirct){
    if(dp[x][y][dirct]!=INF) return dp[x][y][dirct];//이미 방문한 곳이라면 dp값 반환.
    if(x==n-1 && y==m-1) return a[x][y];//최종 지점에 도달한 경우.
    
    check[x][y]=true;//방문 표시.
    int sum=INF;
    for(int i=0; i<3; i++){
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
        if(check[nx][ny]) continue;
        sum = max(sum, go(nx,ny,i));//도달했을 때의 최댓값으로 sum값을 갱신한다.
    }
    check[x][y]=false;//방문 표시 해제.
    dp[x][y][dirct] = a[x][y] + sum;//반환받은 미래 경로의 최댓값에서 현재 위치 원소값을 더해서 dp값을 갱신한다.
    return dp[x][y][dirct];
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> a[i][j];
            dp[i][j][0]=INF;//음의 최댓값으로 dp를 초기화.
            dp[i][j][1]=INF;
            dp[i][j][2]=INF;
        }
    }
    
    check[0][0]=true;
    cout << go(0, 0, 0);
    
    return 0;
}
