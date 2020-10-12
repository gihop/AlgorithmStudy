#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <algorithm>

using namespace std;

//인구_이동 문제 복습
//8달 전에 풀었을 때는 어려웠던 것으로 기억하는데 쉽게 풀었다.

int n, l, r;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> l >> r;
    
    vector<vector<int>> population(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> population[i][j];
        }
    }
    
    int answer = 0;
    
    while (true) {
        bool alliance = false;
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        int num = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (visited[i][j]) continue;
                int count = 1;
                int sum = population[i][j];
                visited[i][j] = true;
                queue<pair<int, int>> q;
                vector<pair<int, int>> position;
                position.push_back(make_pair(i, j));
                q.emplace(i, j);
                while (!q.empty()) {
                    int x, y;
                    tie(x, y) = q.front();
                    q.pop();
                    for (int k = 0; k < 4; k++) {
                        int nx = x + dx[k], ny = y + dy[k];
                        if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                        if (visited[nx][ny]) continue;
                        int diff = max(population[nx][ny], population[x][y]) - min(population[nx][ny], population[x][y]);
                        if (diff >= l && diff <= r) {
                            q.emplace(nx, ny);
                            sum += population[nx][ny];
                            visited[nx][ny] = true;
                            count++;
                            position.push_back(make_pair(nx, ny));
                        }
                    }
                }
                if (position.size() > 1) {
                    alliance = true;
                    int next = sum / count;
                    for (int k = 0; k < position.size(); k++) {
                        int x, y;
                        tie(x, y) = position[k];
                        population[x][y] = next;
                    }
                }
            }
        }
        
        if (!alliance) break;
        else answer++;
    }
    
    cout << answer << endl;
    
    return 0;
}
