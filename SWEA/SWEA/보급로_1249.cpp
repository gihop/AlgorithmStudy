//
//  보급로_1249.cpp
//  SWEA
//
//  Created by jiho park on 2020/10/08.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>
#include <cstring>

using namespace std;

//dp와 bfs를 활용한 문제.

int a[100][100];
int dp[100][100];
int n;
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int main(){
    int tc;
    cin >> tc;
    
    for(int i=0; i<tc; i++){
        cin >> n;
        
        for(int j=0; j<n; j++){
            for(int k=0; k<n; k++){
                scanf("%1d", &a[j][k]);
            }
        }
        
        memset(dp, -1, sizeof(dp));
        
        dp[0][0] = a[0][0];
        
        queue<pair<int,int>> q;
        q.emplace(0,0);
        
        while(!q.empty()){
            int x, y;
            tie(x, y) = q.front();
            q.pop();
            if(x == n-1 && y == n-1) continue;
            for(int j=0; j<4; j++){
                int nx = x+dx[j], ny = y+dy[j];
                if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                if(dp[nx][ny] == -1 || dp[nx][ny] > dp[x][y] + a[nx][ny]){
                    q.emplace(nx, ny);
                    dp[nx][ny] = dp[x][y] + a[nx][ny];
                }
            }
        }
        
        cout << "#" << i+1 << " " << dp[n-1][n-1] << endl;
    }
    
    return 0;
}
