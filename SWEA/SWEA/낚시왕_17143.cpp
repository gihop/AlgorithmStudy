#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

//상어를 이동시킬 때 애를 조금 먹었다.

int r, c, m;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> r >> c >> m;
    
    vector<vector<tuple<int, int, int>>> a(r, vector<tuple<int, int,int>>(c, make_tuple(0, 0, 0)));
    
    for (int i = 0; i < m; i++) {
        int x, y, s, d, z;
        cin >> x >> y >> s >> d >> z;
        x -= 1;
        y -= 1;
        if (d == 1) d = 3;
        else if (d == 2) d = 1;
        else if (d == 3) d = 0;
        else d = 2;
        a[x][y] = make_tuple(z, s, d);
    }
    
    int answer = 0;
    
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            int size, speed, dir;
            tie(size, speed, dir) = a[j][i];
            if (size > 0) {
                answer += size;
                a[j][i] = make_tuple(0, 0, 0);
                break;
            }
        }
        
        vector<vector<vector<tuple<int, int, int>>>> move(r, vector<vector<tuple<int, int, int>>>(c));
        
        for (int j = 0; j < r; j++) {
            for (int k = 0; k < c; k++) {
                int size, speed, dir;
                tie(size, speed, dir) = a[j][k];
                if (size > 0) {
                    int nx = j, ny = k;
                    int next = 0;
                    if (dir == 0 || dir == 2) next = (speed) % ((c - 1) * 2);
                    else next = (speed) % ((r - 1) * 2);
                    
                    while (next--) {
                        nx += dx[dir];
                        ny += dy[dir];
                        if (nx < 0 || nx >= r || ny < 0 || ny >= c) {
                            nx -= dx[dir];
                            ny -= dy[dir];
                            dir = (dir + 2) % 4;
                            next++;
                        }
                    }
                    
                    a[j][k] = make_tuple(0, 0, 0);
                    move[nx][ny].push_back(make_tuple(size, speed, dir));
                }
            }
        }
        
        for (int j = 0; j < r; j++) {
            for (int k = 0; k < c; k++) {
                if (move[j][k].size() > 0) {
                    sort(move[j][k].begin(), move[j][k].end());
                    int size, speed, dir;
                    tie(size, speed, dir) = move[j][k][move[j][k].size() - 1];
                    a[j][k] = make_tuple(size, speed, dir);
                }
            }
        }
    }
    
    cout << answer << endl;
    
    return 0;
}
