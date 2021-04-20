#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <cstring>
#include <map>
 
using namespace std;

/*
 문제에서 놓쳤던 부분은 출발지는 서로 달라도 도착지는 서로 같을 수 있다는 점이다.
 그래서 출발지를 key로 하고 도착지를 value로 하는 map을 생성했다.
 또한 bfs에서 틀리기 쉬운 부분을 간과했다.
 밑에 주석 참고.
 */

int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };
bool visited[20][20];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, now_fuel;
    cin >> n >> m >> now_fuel;

    vector<vector<int>> a(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            if (a[i][j] == 1) a[i][j] = -1;
        }
    }
    map<pair<int, int>, pair<int, int>> cord;
    int start_x, start_y;
    cin >> start_x >> start_y;
    start_x--;
    start_y--;

    for (int i = 0; i < m; i++) {
        int x, y, d_x, d_y;
        cin >> x >> y >> d_x >> d_y;
        a[x-1][y-1] = i + 2;
        cord[make_pair(x - 1, y - 1)] = make_pair(d_x - 1, d_y - 1);
    }
    int success = 0;
    while (true) {
        if (success == m) {
            cout << now_fuel;
            break;
        }
        else if (now_fuel == 0) {
            cout << -1;
            break;
        }
        int next_x=-1, next_y, next_fuel = 0;
        queue<tuple<int, int, int>> q;
        q.emplace(start_x, start_y, now_fuel);
        memset(visited, false, sizeof(visited));
        visited[start_x][start_y] = true;
        while (!q.empty()) {
            int x, y, fuel;
            tie(x, y, fuel) = q.front();
            q.pop();
            if (a[x][y] > 0 && fuel >= next_fuel) { // 이 부분에서도 연료를 검사해야 하는 이유는 bfs 특성상 승객과의 최단거리 3일 때 승객이 아닌곳 거리 3에서 q에 추가되고 승객이 있는 거리 3에서 next_fuel이 정해진 후 거리 4에 승객이 있으면 여기 값이 들어가게 된다.
                if (next_x == -1) {
                    next_x = x;
                    next_y = y;
                    next_fuel = fuel;
                }
                else {
                    if (next_x > x) {
                        next_x = x;
                        next_y = y;
                    }
                    else if (next_x == x && next_y > y) {
                        next_x = x;
                        next_y = y;
                    }
                }
                continue;
            }
            if (fuel == 0 || fuel <= next_fuel) continue;
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                if (a[nx][ny] == -1) continue;
                if (visited[nx][ny]) continue;
                visited[nx][ny] = true;
                q.emplace(nx, ny, fuel-1);
            }
        }
        if (next_fuel == 0 || next_x == -1) {
            cout << -1;
            break;
        }
        int dest_x, dest_y;
        tie(dest_x, dest_y) = cord[make_pair(next_x, next_y)];
        a[next_x][next_y] = 0;
        queue<tuple<int, int, int>> q2;
        memset(visited, false, sizeof(visited));
        q2.emplace(next_x, next_y, next_fuel);
        visited[next_x][next_y] = true;
        bool found = false;
        while (!q2.empty()) {
            int x, y, fuel;
            tie(x, y, fuel) = q2.front();
            q2.pop();
            
            if (x == dest_x && y == dest_y) {
                next_fuel = fuel + (next_fuel - fuel) * 2;
                start_x = x;
                start_y = y;
                found = true;
                break;
            }
            if (fuel == 0) continue;
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                if (visited[nx][ny]) continue;
                if (a[nx][ny] == -1) continue;
                visited[nx][ny] = true;
                q2.emplace(nx, ny, fuel - 1);
            }
        }
        if (found) {
            now_fuel = next_fuel;
            success++;
        }
        else {
            cout << -1;
            break;
        }
    }

    return 0;
}

