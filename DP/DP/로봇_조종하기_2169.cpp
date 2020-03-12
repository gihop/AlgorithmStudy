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

int n,m;
int a[1000][1000];
int dp[1000][1000][3];
bool check[1000][1000];
int dx[]={0, 1, 0};
int dy[]={1, 0, -1};
int INF=-987654321;

int go(int x, int y, int dirct){
    if(dp[x][y][dirct]!=INF) return dp[x][y][dirct];
    if(x==n-1 && y==m-1) return a[x][y];
    
    check[x][y]=true;
    int sum=INF;
    for(int i=0; i<3; i++){
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
        if(check[nx][ny]) continue;
        sum = max(sum, go(nx,ny,i)); // 이부분
    }
    check[x][y]=false;
    dp[x][y][dirct] = a[x][y] + sum;
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
            dp[i][j][0]=INF;
            dp[i][j][1]=INF;
            dp[i][j][2]=INF;
        }
    }
    
    check[0][0]=true;
    cout << go(0, 0, 0);
    
    return 0;
}
