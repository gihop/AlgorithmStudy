#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

//bfs로 최단거리를 구하면서 풀었다.

//이 문제를 풀면서 크게 두 가지 실수를 했다.
//첫 번째는 최단거리 승객이 여러명인 경우, 행, 열이 작은 순서대로 태워야 하는데
//승객 번호가 작은 순서로 태웠었다.

//다음 실수는 찾는데 꼬박 하루가 걸렸다.
//이 실수를 찾은 테스트케이스는 밑에 주석처리 해뒀고,
//실수 코드는 밑에 적었다.

int n, m, fuel;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m >> fuel;
    
    vector<vector<int>> a(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    
    int now_x, now_y;
    cin >> now_x >> now_y;
    now_x -= 1;
    now_y -= 1;
    
    map<pair<int, int>, int> start;
    map<int, pair<int,int>> dest;
    vector<bool> arrived(m, false);
    for (int i = 0; i < m; i++) {
        int start_x, start_y, dest_x, dest_y;
        cin >> start_x >> start_y >> dest_x >> dest_y;
        start[make_pair(start_x-1, start_y-1)] = i;
        dest[i] = make_pair(dest_x-1, dest_y-1);
    }
    int answer = 0;
    
    while (true) {
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        visited[now_x][now_y] = true;
        queue<tuple<int, int, int>> q;
        q.emplace(now_x, now_y, 0);
        bool found = false;
        int Min = 0;
        vector<tuple<int, int, int>> next;
        
        //태워야할 최단 거리 승객 찾기.
        while (!q.empty()) {
            int x, y, distance;
            tie(x, y, distance) = q.front();
            q.pop();
            if (distance > fuel) continue;
            
            //바로 이 부분이 없어서 틀렸었다.
            //밑에 if(found)는 최단거리 3인 승객을 찾았을 때, 거리가 3이거나 그 이상인데
            //승객을 못찾았을 경우 큐에서 거르기 위한 용도다.
            //하지만 bfs의 특성상 최단 거리 3인 처음 승객을 찾았을 때, found가 true가 되지만
            //이전에 거리가 3인데 found가 false여서 거리가 4인 위치가 큐에 추가되어있을 수 있다.
            //이 때 거리가 4인 곳에 승객이 있을 경우, 밑의 if(start.count...)문을 들어가게 된다.
            //그러면 Min의 값이 4로 바뀐다.(3이어야 하는데)
            //그러면 next에서 거리가 3인 최단 거리 승객을 찾았는데 소모된 연료는 4가 된다.
            //이를 해결하기 위해서 밑의 if문을 추가하거나 애초에 next에 int 4개의 튜플을 저장해서
            //맨 처음 값을 거리 값을 주고 sort를 하면 이런 오류가 없었을 것이다.
            if (found && distance > Min) continue;
            
            if (start.count(make_pair(x, y)) > 0 && !arrived[start[make_pair(x,y)]]) {
                next.push_back(make_tuple(x, y, start[make_pair(x, y)]));
                Min = distance;
                found = true;
                continue;
            }
            if (found) {
                continue;
            }
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                if (a[nx][ny] == 1) continue;
                if (visited[nx][ny]) continue;
                visited[nx][ny] = true;
                q.emplace(nx, ny, distance + 1);
            }
        }
        
        //연료로 도달 가능한 거리에 승객이 없는 경우.
        if (next.size() == 0) {
            answer = -1;
            break;
        }
        
        //최단거리 승객중 행, 열 순서로 가장 작은 승객 위치 정렬.
        sort(next.begin(), next.end());
        int now_num = 0;
        tie(now_x, now_y, now_num) = next[0];
        int dest_x, dest_y;
        tie(dest_x, dest_y) = dest[now_num];
        
        fuel -= Min;
        
        visited.clear();
        visited.resize(n, vector<bool>(n, false));
        visited[now_x][now_y] = true;
        found = false;
        Min = 0;
        q.emplace(now_x, now_y, 0);
        
        //승객의 도착지점 최단거리로 이동.
        while (!q.empty()) {
            int x, y, distance;
            tie(x, y, distance) = q.front();
            q.pop();
            if (distance > fuel) continue;
            if (x == dest_x && y == dest_y) {
                found = true;
                Min = distance;
                break;
            }
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                if (a[nx][ny] == 1) continue;
                if (visited[nx][ny]) continue;
                visited[nx][ny] = true;
                q.emplace(nx, ny, distance + 1);
            }
        }
        if (!found) {
            answer = -1;
            break;
        }
        //이미 태운 승객 표시.
        arrived[now_num] = true;
        fuel += Min;
        m--;
        now_x = dest_x;
        now_y = dest_y;
        if (m == 0) {
            answer = fuel;
            break;
        }
    }
    
    cout << answer << endl;
    
    return 0;
}
/*
 5 5 4
 0 0 0 0 0
 0 0 0 0 0
 0 0 0 0 0
 0 0 0 0 0
 0 0 0 0 0
 3 3
 2 2 4 2
 4 2 4 4
 4 4 2 4
 2 4 2 2
 2 5 3 3
 */
