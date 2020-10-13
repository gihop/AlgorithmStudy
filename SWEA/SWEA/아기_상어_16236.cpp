#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

int n;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

int main() {
    cin >> n;
    
    vector<vector<int>> a(n, vector<int>(n, 0));
    
    int shark_x, shark_y, shark_size = 2, shark_eaten = 0;
    vector<tuple<int, int, int, bool>> fishes;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            if (a[i][j] == 9) {
                shark_x = i;
                shark_y = j;
                a[i][j] = 0;
            }
            else if (a[i][j] > 0) fishes.push_back(make_tuple(a[i][j], i, j, false));
        }
    }
    
    int answer = 0;
    sort(fishes.begin(), fishes.end());
    
    while (true) {
        bool canEating = false;
        
        for (int i = 0; i < fishes.size(); i++) {
            int size, x, y;
            bool eaten;
            tie(size, x, y, eaten) = fishes[i];
            if (size >= shark_size) break;
            else if (size < shark_size && !eaten) {
                canEating = true;
                break;
            }
        }
        if (!canEating) break;
        
        queue<tuple<int, int, int>> q;
        q.emplace(shark_x, shark_y, 0);
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        visited[shark_x][shark_y] = true;
        bool found = false;
        int Min = 0;
        vector<pair<int, int>> next;
        while (!q.empty()) {
            int x, y, distance;
            tie(x, y, distance) = q.front();
            q.pop();
            if (found && Min < distance) continue;
            if (a[x][y] > 0 && a[x][y] < shark_size) {
                found = true;
                next.push_back(make_pair(x, y));
                Min = distance;
                continue;
            }
            if (found) continue;
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                if (a[nx][ny] > shark_size) continue;
                if (visited[nx][ny]) continue;
                visited[nx][ny] = true;
                q.emplace(nx, ny, distance+1);
            }
        }
        if (!found) break;
        sort(next.begin(), next.end());
        int nx, ny;
        tie(nx, ny) = next[0];
        a[nx][ny] = 0;
        shark_x = nx;
        shark_y = ny;
        shark_eaten++;
        for (int i = 0; i < fishes.size(); i++) {
            int fish_size, fish_x, fish_y;
            bool fish_eaten;
            tie(fish_size, fish_x, fish_y, fish_eaten) = fishes[i];
            if (fish_x == nx && fish_y == ny) {
                fishes[i] = make_tuple(fish_size, fish_x, fish_y, true);
                break;
            }
        }
        if (shark_eaten == shark_size) {
            shark_eaten = 0;
            shark_size++;
        }
        answer+=Min;
    }
    
    cout << answer << endl;
    
    return 0;
}
