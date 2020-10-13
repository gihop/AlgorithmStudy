#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <tuple>
#include <cstdio>

using namespace std;

//무난한 구현 문제.

int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int tc;
    cin >> tc;
    
    for (int test = 0; test < tc; test++) {
        int n, m;
        cin >> n >> m;
        
        int now_x, now_y;
        vector<vector<char>> a(n, vector<char>(m, '.'));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
                if (a[i][j] == 'S') {
                    now_x = i;
                    now_y = j;
                }
            }
        }
        
        bool alive = true;
        bool success = false;
        int time = 0;
        while (alive) {
            alive = false;
            
            vector<pair<int, int>> cursed;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (a[i][j] == '*') {
                        for (int dir = 0; dir < 4; dir++) {
                            int nx = i + dx[dir], ny = j + dy[dir];
                            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                            if (a[nx][ny] == '.' || a[nx][ny] == 'S') {
                                cursed.push_back(make_pair(nx, ny));
                            }
                        }
                    }
                }
            }
            
            vector<pair<int, int>> moved;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (a[i][j] == 'S') {
                        for (int dir = 0; dir < 4; dir++) {
                            int nx = i + dx[dir], ny = j + dy[dir];
                            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                            if (a[nx][ny] == '.') {
                                alive = true;
                                moved.push_back(make_pair(nx, ny));
                            }
                            else if (a[nx][ny] == 'D') {
                                success = true;
                                break;
                            }
                        }
                    }
                    if (success) break;
                }
                if (success) break;
            }
            if (success) break;
            
            for (int i = 0; i < moved.size(); i++) {
                int moved_x, moved_y;
                tie(moved_x, moved_y) = moved[i];
                a[moved_x][moved_y] = 'S';
            }
            
            for (int i = 0; i < cursed.size(); i++) {
                int cursed_x, cursed_y;
                tie(cursed_x, cursed_y) = cursed[i];
                a[cursed_x][cursed_y] = '*';
            }
            time++;
        }
        if (success) cout << "#" << test + 1 << " " << time+1 << endl;
        else cout << "#" << test + 1 << " GAME OVER" << endl;
    }
    
    return 0;
}
