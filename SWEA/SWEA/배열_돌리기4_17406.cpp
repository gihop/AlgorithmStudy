#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

//배열_돌리기4 재시도.

int n, m, k;
vector<vector<int>> a;
vector<tuple<int, int, int>> op;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };
vector<bool> visited;
int ans = 987654321;

void spin(int r, int c, int s, vector<vector<int>> &Map) {
    int x = r, y = c;
    for (int i = 1; i <= s; i++) {
        x = r - i;
        y = c - i;
        int tmp = Map[x][y];
        int nx = x, ny = y;
        for (int j = 0; j < i * 2; j++) {
            nx += dx[1];
            ny += dy[1];
            Map[x][y] = Map[nx][ny];
            x = nx;
            y = ny;
        }
        for (int j = 0; j < i * 2; j++) {
            nx += dx[0];
            ny += dy[0];
            Map[x][y] = Map[nx][ny];
            x = nx;
            y = ny;
        }
        for (int j = 0; j < i * 2; j++) {
            nx += dx[3];
            ny += dy[3];
            Map[x][y] = Map[nx][ny];
            x = nx;
            y = ny;
        }
        for (int j = 0; j < i * 2 - 1; j++) {
            nx += dx[2];
            ny += dy[2];
            Map[x][y] = Map[nx][ny];
            x = nx;
            y = ny;
        }
        Map[x][y] = tmp;
    }
}

void go(int count, vector<int> order) {
    if (count == k) {
        vector<vector<int>> Map = a;
        for (int i = 0; i < order.size(); i++) {
            int r, c, s;
            tie(r, c, s) = op[order[i]];
            spin(r, c, s, Map);
        }
        
        int Min = 987654321;
        for (int i = 0; i < n; i++) {
            int sum = 0;
            for (int j = 0; j < m; j++) {
                sum += Map[i][j];
            }
            if (sum < Min) Min = sum;
        }
        if (Min < ans) ans = Min;
        
        return;
    }
    for (int i = 0; i < k; i++) {
        if (visited[i]) continue;
        order.push_back(i);
        visited[i] = true;
        go(count + 1, order);
        visited[i] = false;
        order.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m >> k;
    
    a.resize(n, vector<int>(m, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    
    for (int i = 0; i < k; i++) {
        int r, c, s;
        cin >> r >> c >> s;
        op.push_back(make_tuple(r-1, c-1, s));
    }
    
    visited.resize(k, false);
    vector<int> order;
    
    go(0, order);
    
    cout << ans;
    
    
    return 0;
}

