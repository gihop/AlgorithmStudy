//
//  욕심쟁이_판다_1937.cpp
//  DP
//
//  Created by jiho park on 2020/03/09.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>

#define endl "\n"
using namespace std;

//무난한 dp 문제.

int a[501][501];
int dp[501][501];
int n;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};
int ans;

int go(int x, int y){
    int num = a[x][y];
    
    if(dp[x][y]!=-1) return dp[x][y];
    
    int day=1;
    for(int i=0; i<4; i++){
        int nday=1;
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(nx<0 || nx>=n || ny<0 || ny>=n) continue;
        if(a[nx][ny]>num){//이전 지역보다 대나무가 많은 경우.
            nday+=go(nx,ny);
            if(nday>day) day = nday;//모든 방향중 가장 멀리 갈 수 있는 곳만 저장.
        }
    }
    dp[x][y]=day;
    
    return dp[x][y];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    memset(dp, -1, sizeof(dp));
    
    cin >> n;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> a[i][j];
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int num = go(i,j);
            if(num > ans) ans = num;
        }
    }
    
    cout << ans;
    
    return 0;
}
