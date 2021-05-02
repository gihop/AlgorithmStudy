#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <iostream>

using namespace std;

/*
 이전에 풀었던 방법보다 훨씬 간결하게 풀었다.
 */

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int solution(vector<vector<int>> board) {
    int answer = 0;
    int n = board.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    queue<tuple<int,int,int,int>> q;
    q.emplace(0, 0, -1, 0);
    dp[0][0] = 0;
    while(!q.empty()){
        int x, y, dir, cost;
        tie(x, y, dir, cost) = q.front();
        q.pop();
        if(dp[x][y] < cost) continue;
        if(x == n-1 && y == n-1) continue;
        for(int i=0; i<4; i++){
            int nx = x+dx[i], ny = y+dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if(board[nx][ny] == 1) continue;
            int now_cost = 100;
            if(dir != -1 && dir != i) now_cost += 500;
            if(dp[nx][ny] == -1 || (dp[nx][ny] >= dp[x][y] + now_cost)){
                dp[nx][ny] = dp[x][y] + now_cost;
                q.emplace(nx, ny, i, cost+now_cost);
            }
        }
    }
    
    return dp[n-1][n-1];
}
