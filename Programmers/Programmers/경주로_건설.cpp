#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <iostream>

using namespace std;

//bfs와 dp를 활용해서 풀었다.

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int solution(vector<vector<int>> board) {
    int answer = 987654321;
    int N = board.size();
    vector<vector<int>> dp(N, vector<int>(N, -1));
    dp[0][0] = 0;
    queue<tuple<int,int,int,int>> q;
    q.emplace(0, 0, -1, 0);
    
    while(!q.empty()){
        int x, y, pre, cost;
        tie(x, y, pre, cost) = q.front();
        q.pop();
        
        if(cost >= answer) continue;
        if(x == N-1 && y == N-1){
            answer = cost;
            continue;
        }
        for(int i=0; i<4; i++){
            int nx = x+dx[i], ny = y+dy[i];
            if(nx<0 || nx>=N || ny<0 || ny>=N) continue;
            if(board[nx][ny]==1) continue;
            if(pre == -1) {
                q.emplace(nx, ny, i, 100);
                dp[nx][ny] = 100;
            }
            else{
                if(pre != i){
                    if(dp[nx][ny] == -1 || dp[nx][ny] >= cost+600){
                        q.emplace(nx, ny, i, cost+600);
                        dp[nx][ny] = cost+600;
                    }
                }
                else if(dp[nx][ny] == -1 || dp[nx][ny] >= cost+100){
                    q.emplace(nx, ny, i, cost+100);
                    dp[nx][ny] = cost+100;
                }
            }
        }
    }
    
    return answer;
}
