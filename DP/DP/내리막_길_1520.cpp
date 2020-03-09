//
//  내리막_길_1520.cpp
//  DP
//
//  Created by jiho park on 2020/03/09.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>

#define endl "\n"
using namespace std;

//많이 봤던 dp 유형 문제.

int a[501][501];
int dp[501][501];
int n, m;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int go(int x, int y){
    if(x==n-1 && y==m-1) return 1;
    
    if(dp[x][y]!=-1) return dp[x][y];
    
    int num = a[x][y];
    int sum=0;
    for(int i=0; i<4; i++){
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
        if(a[nx][ny] < num) sum+=go(nx,ny);//내리막인 경우에만 이동.
    }
    dp[x][y]=sum;
    
    return dp[x][y];
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
    
    cout << go(0,0);
    
    return 0;
}
