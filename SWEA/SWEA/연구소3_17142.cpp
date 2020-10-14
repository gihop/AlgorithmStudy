#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

//연구소3_17142 재시도.
//생각보다 간단한 문제였는데 너무 어렵게 생각했다.

//처음에는 매 초마다 bfs를 하는 것으로 구현했는데 이는 시간초과를 발생시켰다.
//매 초마다 bfs로 값을 퍼져나가게 해서 더이상 퍼져나가지 않게 되면
//bfs를 감싼 for문의 인자값을 출력하도록 했었다.
//하지만 시간초과.

//다음 방법으로 지도에서 bfs의 카운트를 맵에 갱신시켰는데
//여기서 많이 해맸었다.
//하지만 간단하게 생각하면 비활성화 바이러스는 최종으로 가장 큰 시간을 가진 count의 값을
//맵에서 탐색할 때 배제 시키면 되는 것이다.
//또한 비활성화된 바이러스에서 bfs를 돌리면 해당 비활성화 바이러스의 값은 다시 다른 값으로 바꿔줘야 한다.
//그렇지 않으면 바로 옆에 비활성화된 값이 또 있을 때 무한루프를 돌게 된다.

int n, m;
vector<vector<int>> a;
vector<pair<int, int>> virus;
vector<bool> check;
int answer = 987654321;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

void go(int idx, int cnt) {
    if (cnt == m) {
        vector<vector<int>> map = a;
        queue<tuple<int, int, int>> q;
        for (int i = 0; i < virus.size(); i++) {
            if (check[i]) {
                int x, y;
                tie(x, y) = virus[i];
                q.emplace(x, y, 0);
                map[x][y] = 0;
            }
        }
        
        while (!q.empty()) {
            int x, y, count;
            tie(x, y, count) = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                if (map[nx][ny] == -1) {
                    q.emplace(nx, ny, count + 1);
                    map[nx][ny] = count + 1;
                }
                else if (map[nx][ny] == -3) {
                    q.emplace(nx, ny, count + 1);
                }
            }
            if(map[x][y] == -3) map[x][y] = -4;
        }
        
        bool success = true;
        int Max = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (map[i][j] == -1) {
                    success = false;
                    break;
                }
                if (map[i][j] >= 0 && Max < map[i][j])
                    Max = map[i][j];
            }
            if (!success) break;
        }
        if (success && answer > Max) {
            answer = Max;
        }
        
        return;
    }
    for (int i = idx; i < check.size(); i++) {
        if (check[i]) continue;
        check[i] = true;
        go(i, cnt + 1);
        check[i] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m;
    
    a.resize(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            if (a[i][j] == 2) {
                virus.push_back(make_pair(i, j));
                a[i][j] = -3;
            }
            else if (a[i][j] == 1) a[i][j] = -2;
            else if (a[i][j] == 0) a[i][j] = -1;
        }
    }
    check.resize(virus.size(), false);
    
    go(0, 0);
    
    if (answer == 987654321) cout << -1 << "\n";
    else cout << answer << "\n";
    
    return 0;
}
