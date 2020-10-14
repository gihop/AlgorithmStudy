#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

//

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
        
        bool found = false;
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
