#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, q;
    cin >> n >> q;
    int N = 1;
    for (int i = 0; i < n; i++)
        N *= 2;

    vector<vector<int>> a(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> a[i][j];
        }
    }

    vector<int> order(q, 0);
    for (int i = 0; i < q; i++) {
        int l;
        cin >> l;
        order[i] = l;
    }
        
    for (int s = 0; s < order.size(); s++) {
        int L = 1;
        for (int i = 0; i < order[s]; i++)
            L *= 2;

        for (int i = 0; i < N; i += L) {
            for (int j = 0; j < N; j += L) {
                vector<vector<int>> v(L, vector<int>(L, 0));
                for (int k = 0; k < L; k++) {
                    for (int o = 0; o < L; o++) {
                        v[k][o] = a[k + i][o + j];
                    }
                }
                for (int k = 0; k < L; k++) {
                    for (int o = 0; o < L; o++) {
                        a[o + i][L - k + j - 1] = v[k][o];
                    }
                }
            }
        }

        vector<vector<int>> next;
        next.assign(a.begin(), a.end());

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (a[i][j] == 0) continue;
                int count = 0;
                for (int d = 0; d < 4; d++) {
                    int nx = i + dx[d], ny = j + dy[d];
                    if (nx >= 0 && nx < N && ny >= 0 && ny < N && a[nx][ny] > 0) {
                        count++;
                    }
                }
                if (count < 3)
                    next[i][j]--;
            }
        }
        a.assign(next.begin(), next.end());
        next.clear();
    }

    int sum = 0;
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum += a[i][j];
        }
    }
    int max = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!visited[i][j] && a[i][j] > 0) {
                visited[i][j] = true;
                queue<pair<int, int>> q;
                q.emplace(i, j);
                int now = 1;
                while (!q.empty()) {
                    int x, y;
                    tie(x, y) = q.front();
                    q.pop();
                    for (int k = 0; k < 4; k++) {
                        int nx = x + dx[k], ny = y + dy[k];
                        if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                        if (visited[nx][ny]) continue;
                        if (a[nx][ny] == 0) continue;
                        visited[nx][ny] = true;
                        now += 1;
                        q.emplace(nx, ny);
                    }
                }
                if (now > max) max = now;
            }
        }
    }

    cout << sum << '\n';
    cout << max;

    return 0;
}
