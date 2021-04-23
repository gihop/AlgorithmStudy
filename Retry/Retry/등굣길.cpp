#include <string>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

/*
 인풋의 좌표는 모두 행,열 순서가 아니라 열,행이다.
 그래서 틀렸었다.
 */

int INF = 1000000007;

int dx[] = {0, 1};
int dy[] = {1, 0};

int solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;
    
    vector<vector<int>> a(n, vector<int>(m, 0));
    for(int i=0; i<puddles.size(); i++){
        a[puddles[i][1]-1][puddles[i][0]-1] = -1;
    }
    a[0][0] = 1;
    queue<pair<int,int>> q;
    q.emplace(0,0);
    while(!q.empty()){
        int x, y;
        tie(x, y) = q.front();
        q.pop();
        for(int i=0; i<2; i++){
            int nx = x+dx[i], ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
            if(a[nx][ny] == -1) continue;
            if(a[nx][ny] == 0) q.emplace(nx, ny);
            a[nx][ny] += a[x][y];
            a[nx][ny] %= INF;
        }
    }
    
    return a[n-1][m-1];
}
