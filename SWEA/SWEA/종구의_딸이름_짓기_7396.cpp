#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

//테스트케이스는 맞았는데 계속 런타임에러가 발생했다.
//bfs로 아래 위 모든 방향으로 가면서 dp string 벡터를 이용해서 계속 작은 값을 갖도록하고
//dp[n-1][m-1]을 정답으로 출력하도록 했다.
//하지만 이렇게 했을 때, string의 길이가 4000이 넘어가는데 아마 이 부분 때문에 런타임 에러가
//발생한 것 같다.

//이를 해결하기 위해서 아래 위 방향을 이동할 때 무조건 크기가 작은 문자 방향으로 가야 정답인 것을 이용했다.
//즉 아래 위 방향중에 크기가 작은 쪽으로만 이동을한다.
//하지만 아래 위 방향 글자 크기가 같은 경우가 문제다.
//이 때 큐를 하나 더 만들어서 새로운 큐에만 다음 위치를 넣고 탐색이 끝나면 새로운 큐 값들을
//기존의 큐에 넣어서 갱신시키는 방식으로 해결했다.
//즉 현 위치에서 두 가지 방향을 탐색을 할 때,
//현 시점 가장 작은 값을 "z"로 놓고, 탐색할 때 현재 Min 값보다 더 작은 값이 나오면 nq를 비우고
//그 값을 넣는다.
//하지만 같은 값이 나온다면 nq에 두개를 넣는다.
//탐색이 끝나면 answer string에 가장 작은 값인 Min을 더한다.
//이렇게 하면 answer는 가장 작은 문자열로만 구성된다.

int dx[] = { 0, 1 };
int dy[] = { 1, 0 };

int main(int argc, char** argv){
    int test_case;
    int T;
    
    //freopen("input.txt", "r", stdin);
    cin >> T;
    
    for (test_case = 1; test_case <= T; ++test_case){
        int n, m;
        cin >> n >> m;
        
        vector<vector<string>> a(n, vector<string>(m, ""));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                char c;
                cin >> c;
                a[i][j] += c;
            }
        }
        
        string ans = "";
        ans += a[0][0];
        
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        queue<pair<int, int>> q, nq;
        
        q.emplace(0, 0);
        while (ans.size() < n + m - 1) {
            string Min = "z";
            while (!q.empty()) {
                int x, y;
                tie(x, y) = q.front();
                q.pop();
                
                if (x == n - 1 && y == m - 1) continue;
                for (int i = 0; i < 2; i++) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                    if (visited[nx][ny]) continue;
                    visited[nx][ny] = true;
                    if (a[nx][ny] < Min) {
                        while (!nq.empty()) nq.pop();
                        nq.emplace(nx, ny);
                        Min = a[nx][ny];
                    }
                    else if (a[nx][ny] == Min) {
                        nq.emplace(nx, ny);
                    }
                }
            }
            q = nq;
            ans += Min;
        }
        cout << "#" << test_case<< " " << ans << endl;
        visited.clear();
    }
    
    return 0;
}
