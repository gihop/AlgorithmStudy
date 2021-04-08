#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N=0, M, K;
    cin >> N >> M >> K;

    vector<vector<vector<tuple<int, int, int>>>> a(50, vector<vector<tuple<int,int,int>>>(50));

    for (int i = 0; i < M; i++) {
        int x, y, m, s, d;
        cin >> x >> y >> m >> s >> d;
        a[x - 1][y - 1].push_back(make_tuple(m, s, d));
    }

    while (K--) {
        vector<vector<vector<tuple<int, int, int>>>> next(50, vector<vector<tuple<int, int, int>>>(50));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < a[i][j].size(); k++) {
                    int m, s, d;
                    tie(m, s, d) = a[i][j][k];
                    int move = s % N;
                    int nx = i, ny = j;
                    for (int l = 0; l < move; l++) {
                        nx += dx[d];
                        ny += dy[d];
                        if (nx < 0) nx = N - 1;
                        else if (nx == N) nx = 0;
                        if (ny < 0) ny = N - 1;
                        else if (ny == N) ny = 0;
                    }
                    next[nx][ny].push_back(make_tuple(m, s, d));
                }
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (next[i][j].size() >= 2) {
                    int m_sum = 0, s_sum = 0;
                    int ball_count = next[i][j].size();
                    bool odd = true, even = true;
                    for (int k = 0; k < ball_count; k++) {
                        int m, s, d;
                        tie(m, s, d) = next[i][j][k];
                        m_sum += m;
                        s_sum += s;
                        if (d % 2 == 0) odd = false;
                        else even = false;
                    }
                    next[i][j].clear();
                    if (m_sum / 5 > 0) {
                        if (odd || even) {
                            next[i][j].push_back(make_tuple(m_sum / 5, s_sum / ball_count, 0));
                            next[i][j].push_back(make_tuple(m_sum / 5, s_sum / ball_count, 2));
                            next[i][j].push_back(make_tuple(m_sum / 5, s_sum / ball_count, 4));
                            next[i][j].push_back(make_tuple(m_sum / 5, s_sum / ball_count, 6));
                        }
                        else {
                            next[i][j].push_back(make_tuple(m_sum / 5, s_sum / ball_count, 1));
                            next[i][j].push_back(make_tuple(m_sum / 5, s_sum / ball_count, 3));
                            next[i][j].push_back(make_tuple(m_sum / 5, s_sum / ball_count, 5));
                            next[i][j].push_back(make_tuple(m_sum / 5, s_sum / ball_count, 7));
                        }
                    }
                }
            }
        }

        a.assign(next.begin(), next.end());
        next.clear();
    }

    int answer = 0;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < a[i][j].size(); k++) {
                int m, s, d;
                tie(m, s, d) = a[i][j][k];
                answer += m;
            }
        }
    }

    cout << answer;
    return 0;
}
