#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <queue>
using namespace std;

int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[] = { 0, -1, -1, -1, 0, 1, 1, 1 };

int Max = 0;

void dfs(vector<vector<pair<int, int>>> a, map<int, tuple<int, int, bool>> m, int x, int y, int dir, int count) {
    if (count > Max) Max = count;
    for (int i = 1; i <= 16; i++) {
        int fx, fy;
        bool alive;
        tie(fx, fy, alive) = m[i];
        if (!alive) continue;
        int fdir = a[fx][fy].second;
        for (int j = 0; j < 8; j++) {
            int nx = fx + dx[(fdir + j) % 8], ny = fy + dy[(fdir + j) % 8];
            if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) continue;
            if (nx == x && ny == y) continue;
            if (a[nx][ny].first > 0) {
                int num, ndir;
                tie(num, ndir) = a[nx][ny];
                a[nx][ny] = make_pair(i, (fdir+j)%8);
                a[fx][fy] = make_pair(num, ndir);
                m[num] = make_tuple(fx, fy, true);
                m[i] = make_tuple(nx, ny, true);
            }
            else {
                a[fx][fy] = make_pair(0, 0);
                a[nx][ny] = make_pair(i, (fdir+j)%8);
                m[i] = make_tuple(nx, ny, true);
            }
            break;
        }
    }
    for (int i = 1; i <= 3; i++) {
        int sx = x + (dx[dir] * i), sy = y + (dy[dir] * i);
        if (sx < 0 || sx >= 4 || sy < 0 || sy >= 4) break;
        if (a[sx][sy].first > 0) {
            int num, ndir;
            tie(num, ndir) = a[sx][sy];
            a[sx][sy] = make_pair(0, 0);
            m[num] = make_tuple(sx, sy, false);
            dfs(a, m, sx, sy, ndir, count + num);
            m[num] = make_tuple(sx, sy, true);
            a[sx][sy] = make_pair(num, ndir);
        }
    }
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    map<int, tuple<int, int, bool>> m;
    vector<vector<pair<int, int>>> a(4, vector<pair<int, int>>(4, make_pair(0, 0)));

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int num, dir;
            cin >> num >> dir;
            a[i][j] = make_pair(num, dir-1);
            m[num] = make_tuple(i, j, true);
        }
    }
    int count = a[0][0].first;
    int dir = a[0][0].second;
    m[count] = make_tuple(0, 0, false);
    a[0][0] = make_pair(0, 0);
    
    dfs(a, m, 0, 0, dir, count);
    cout << Max;
    return 0;
}
/*
1 2 2 2 3 2 4 2
5 2 6 7 7 7 8 7
9 4 10 7 11 7 12 7
13 4 14 4 15 4 16 4
*/
