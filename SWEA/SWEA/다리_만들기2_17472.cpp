#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

//다리_만들기2 재시도.
//구현해야할 양이 꽤 많고, 까다로운 문제.

int n, m;
vector<vector<int>> Map;
vector<vector<pair<int, int>>> island(6);
vector<vector<pair<int, int>>> graph;
bool visited[10][10];
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };
int island_count;
int ans = 987654321;
map<pair<int, int>, int> bridge_use;
vector<int> island_visited;

void go(int idx, vector<int> island_visited, int sum) {
    bool success = true;
    for (int i = 0; i < island_visited.size(); i++) {
        if (island_visited[i] == 0) {
            success = false;
            break;
        }
    }
    if (success) {
        if (sum < ans) ans = sum;
        return;
    }
    for (int i = 0; i < graph[idx].size(); i++) {
        int next, cost;
        tie(next, cost) = graph[idx][i];
        if (bridge_use[make_pair(min(idx, next), max(idx, next))] == 0) continue;
        if (bridge_use[make_pair(min(idx, next), max(idx, next))] == 2) {
            bridge_use[make_pair(min(idx, next), max(idx, next))] -= 1;
            island_visited[next] += 1;
            go(next, island_visited, sum + cost);
            island_visited[next] -= 1;
            bridge_use[make_pair(min(idx, next), max(idx, next))] += 1;
        }
        else if (bridge_use[make_pair(min(idx, next), max(idx, next))] == 1) {
            bridge_use[make_pair(min(idx, next), max(idx, next))] -= 1;
            island_visited[next] += 1;
            go(next, island_visited, sum);
            island_visited[next] -= 1;
            bridge_use[make_pair(min(idx, next), max(idx, next))] += 1;
        }
    }
}

void create_bridge(int a, int b) {
    int length = 11;
    for (int i = 0; i < island[a].size(); i++) {
        int a_x, a_y;
        tie(a_x, a_y) = island[a][i];
        for (int j = 0; j < island[b].size(); j++) {
            int b_x, b_y;
            tie(b_x, b_y) = island[b][j];
            if (a_x == b_x) {
                int start = min(a_y, b_y), dest = max(a_y, b_y);
                int diff = dest - start - 1;
                if (diff < 2) continue;
                bool success = true;
                int ny = start;
                for (int k = 0; k < diff; k++) {
                    ny += dy[0];
                    if (Map[a_x][ny] > 0) {
                        success = false;
                        break;
                    }
                }
                if (success) {
                    if (length > diff) length = diff;
                    continue;
                }
            }
            else if (a_y == b_y) {
                int start = min(a_x, b_x), dest = max(a_x, b_x);
                int diff = dest - start - 1;
                if (diff < 2) continue;
                bool success = true;
                int nx = start;
                for (int k = 0; k < diff; k++) {
                    nx += dx[1];
                    if (Map[nx][a_y] > 0) {
                        success = false;
                        break;
                    }
                }
                if (success) {
                    if (length > diff) length = diff;
                    continue;
                }
            }
        }
    }
    if (length != 11) {
        graph[a].push_back(make_pair(b, length));
        graph[b].push_back(make_pair(a, length));
        bridge_use[make_pair(min(a, b), max(a, b))] = 2;
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m;
    
    Map.resize(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> Map[i][j];
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (Map[i][j] > 0 && !visited[i][j]) {
                visited[i][j] = true;
                island_count++;
                Map[i][j] = island_count;
                queue<pair<int, int>> q;
                q.emplace(i, j);
                island[island_count - 1].push_back(make_pair(i, j));
                while (!q.empty()) {
                    int x, y;
                    tie(x, y) = q.front();
                    q.pop();
                    for (int k = 0; k < 4; k++) {
                        int nx = x + dx[k], ny = y + dy[k];
                        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                        if (Map[nx][ny] == 0) continue;
                        if (visited[nx][ny]) continue;
                        visited[nx][ny] = true;
                        Map[nx][ny] = island_count;
                        q.emplace(nx, ny);
                        island[island_count - 1].push_back(make_pair(nx, ny));
                    }
                }
            }
        }
    }
    
    graph.resize(island_count);
    
    for (int i = 0; i < island_count; i++) {
        for (int j = i+1; j < island_count; j++) {
            create_bridge(i, j);
        }
    }
    
    vector<int> island_visited(island_count, 0);
    go(0, island_visited, 0);
    
    if (ans == 987654321) cout << -1;
    else cout << ans;
    
    return 0;
}
