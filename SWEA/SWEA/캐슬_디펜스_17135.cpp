#include <iostream>
#include <queue>
#include <tuple>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>

using namespace std;

//캐슬_디펜스 재시도.

int n, m, d;
int dx[] = { 0, 0, -1 };
int dy[] = { 1, -1, 0 };
vector<vector<int>> a;
vector<int> archer;
bool visited[16][15];
int ans = 0;

bool enemy(vector<vector<int>> Map) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (Map[i][j] == 1) {
                found = true;
                break;
            }
        }
        if (found) break;
    }
    return found;
}

void go(int idx, int cnt) {
    if (cnt == 3) {
        vector<vector<int>> Map = a;
        int kill = 0;
        for (int i = 0; i < archer.size(); i++) {
            Map[n][archer[i]] = 1;
        }
        int count = 0;
        while (enemy(Map)) {
            vector<pair<int, int>> killed;
            set<pair<int, int>> s;
            for (int i = 0; i < Map[n].size(); i++) {
                if (Map[n][i] == 1) {
                    memset(visited, false, sizeof(visited));
                    queue<tuple<int, int, int>> q;
                    visited[n - 1][i] = true;
                    q.emplace(n - 1, i, 1);
                    vector<pair<int, int>> close;
                    bool found = false;
                    int Min = 0;
                    while (!q.empty()) {
                        int x, y, distance;
                        tie(x, y, distance) = q.front();
                        q.pop();
                        if (!found && Map[x][y] == 1) {
                            found = true;
                            close.push_back(make_pair(y, x));
                            Min = distance;
                            continue;
                        }
                        else if (found && Map[x][y] == 1 && distance == Min) {
                            close.push_back(make_pair(y, x));
                            continue;
                        }
                        else if (found) continue;
                        else if (distance == d) continue;
                        for (int j = 0; j < 3; j++) {
                            int nx = x + dx[j], ny = y + dy[j];
                            if (nx < 0 || ny < 0 || ny >= m) continue;
                            if (visited[nx][ny]) continue;
                            visited[nx][ny] = true;
                            q.emplace(nx, ny, distance + 1);
                        }
                    }
                    if (close.size() > 0) {
                        sort(close.begin(), close.end());
                        if (s.count(close[0]) == 0) {
                            killed.push_back(close[0]);
                            s.insert(close[0]);
                        }
                    }
                }
            }
            for (int i = 0; i < killed.size(); i++) {
                Map[killed[i].second][killed[i].first] = 0;
            }
            count += killed.size();
            for (int i = 0; i < m; i++) {
                Map[n - 1][i] = 0;
            }
            for (int i = n - 2; i >= 0; i--) {
                for (int j = 0; j < m; j++) {
                    if (Map[i][j] == 1) {
                        Map[i + 1][j] = 1;
                        Map[i][j] = 0;
                    }
                }
            }
        }
        if (count > ans) ans = count;
        
        return;
    }
    for (int i = idx+1; i < m; i++) {
        archer.push_back(i);
        go(i, cnt + 1);
        archer.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m >> d;
    
    a.resize(n + 1, vector<int>(m, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    
    go(-1, 0);
    
    cout << ans << "\n";
    
    return 0;
}
