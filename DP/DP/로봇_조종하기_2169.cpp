//
//  로봇_조종하기_2169.cpp
//  DP
//
//  Created by jiho park on 2020/03/12.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>

#define endl "\n"
using namespace std;

int n,m;
int a[1000][1000];
int dp[1000][1000][3];
bool check[1000][1000];
int dx[]={0, 1, 0};
int dy[]={1, 0, -1};

void go(int x, int y, int sum, int dirct){
    if(dp[x][y][dirct]!=-1 && sum < dp[x][y][dirct]) return;
    dp[x][y][dirct]=sum;
    if(x==n-1 && y==m-1)
        return;
    
    for(int i=0; i<3; i++){
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
        if(check[nx][ny]) continue;
        check[nx][ny]=true;
        int nsum = sum+a[nx][ny];
        go(nx,ny,nsum,i);
        check[nx][ny]=false;
    }
    
    return;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    memset(dp, -1, sizeof(dp));
    
    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> a[i][j];
    
    check[0][0]=true;
    go(0, 0, a[0][0], 0);
    
    int max=0;
    for(int i=0; i<3; i++)
        if(max < dp[n-1][m-1][i]) max = dp[n-1][m-1][i];
    
    cout << max;
    
    return 0;
}
