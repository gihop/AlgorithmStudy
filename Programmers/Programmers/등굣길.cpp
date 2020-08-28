#include <string>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

//변형된 bfs로 풀 수 있었다.
//최적의 이동을 위에서 우, 아래 방향으로만 이동한다.
//처음에 1을 가지고 시작하며, 칸을 이동을 했을 때 이미 이동을 한 흔적이 있다면 큐에 넣지 않는다.
//visited에 이전 숫자를 더한다.
//너비 탐색이므로 이동 횟수에 따라 칸마다 이동할 수 있는 최적의 경우의 수가 저장된다.

long long visited[100][100];
int dx[] = {0, 1};
int dy[] = {1, 0};
int MAX = 1000000007;

int solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;
    
    for(int i=0; i<puddles.size(); i++){
        visited[puddles[i][1]-1][puddles[i][0]-1] = -1;
    }
    
    visited[0][0]=1;
    queue<pair<int,int>> q;
    q.emplace(0,0);
    
    while(!q.empty()){
        int x, y;
        tie(x,y) = q.front();
        q.pop();
        for(int i=0; i<2; i++){
            int nx = x+dx[i];
            int ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
            if(visited[nx][ny] == -1) continue;
            if(visited[nx][ny] == 0)
                q.emplace(nx, ny);
            visited[nx][ny] += visited[x][y];
            visited[nx][ny] %= MAX;
        }
    }
    
    answer = visited[n-1][m-1] % MAX;
    
    return answer;
}
