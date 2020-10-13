#include <iostream>
#include <vector>

using namespace std;

//미세먼지_안녕!_17144 문제 재시도.

int n, m, t;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m >> t;
    
    vector<vector<int>> a(n, vector<int>(m, 0));
    
    int cleaner_top_x = 0, cleaner_top_y = 0, cleaner_bot_x = 0, cleaner_bot_y = 0;
    bool found_top = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            if (a[i][j] == -1 && !found_top) {
                cleaner_top_x = i;
                cleaner_top_y = j;
                found_top = true;
            }
            else if (a[i][j] == -1) {
                cleaner_bot_x = i;
                cleaner_bot_y = j;
            }
        }
    }
    
    for (int i = 0; i < t; i++) {
        vector<vector<vector<int>>> spread(n, vector<vector<int>>(m));
        
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                if (a[j][k] >= 5) {
                    int spread_size = a[j][k] / 5;
                    int count = 0;
                    for (int dir = 0; dir < 4; dir++) {
                        int nx = j + dx[dir], ny = k + dy[dir];
                        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                        if (a[nx][ny] == -1) continue;
                        spread[nx][ny].push_back(spread_size);
                        count++;
                    }
                    a[j][k] -= (spread_size * count);
                }
            }
        }
        
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                for (int idx = 0; idx < spread[j][k].size(); idx++) {
                    a[j][k] += spread[j][k][idx];
                }
            }
        }
        
        int x = cleaner_top_x-1, y = cleaner_top_y;
        a[x][y] = 0;
        while (true) {
            if (x == 0)break;
            a[x][y] = a[x - 1][y];
            x--;
        }
        while (true) {
            if (y == m - 1) break;
            a[x][y] = a[x][y + 1];
            y++;
        }
        while (true) {
            if (x == cleaner_top_x) break;
            a[x][y] = a[x + 1][y];
            x++;
        }
        while (true) {
            if (y == cleaner_top_y + 1) break;
            a[x][y] = a[x][y - 1];
            y--;
        }
        a[x][y] = 0;
        
        x = cleaner_bot_x + 1;
        y = cleaner_bot_y;
        while (true) {
            if (x == n - 1) break;
            a[x][y] = a[x + 1][y];
            x++;
        }
        while (true) {
            if (y == m - 1) break;
            a[x][y] = a[x][y + 1];
            y++;
        }
        while (true) {
            if (x == cleaner_bot_x) break;
            a[x][y] = a[x - 1][y];
            x--;
        }
        while (true) {
            if (y == cleaner_bot_y + 1) break;
            a[x][y] = a[x][y - 1];
            y--;
        }
        a[x][y] = 0;
    }
    
    int answer = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] > 0) answer += a[i][j];
        }
    }
    
    cout << answer << endl;
    
    
    return 0;
}
