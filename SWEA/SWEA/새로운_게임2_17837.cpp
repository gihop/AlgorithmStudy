#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

//파란색으로 이동했을 때, 말 4개 이상 쌓여 게임이 종료되는 조건을 추가하지 않아서 해맸었다.

int n, k;
int dx[] = { 0, 0, -1, 1 };
int dy[] = { 1, -1, 0, 0 };

vector<vector<vector<pair<int, int>>>> horse_position;
vector<tuple<int, int, int>> horse_info;

bool next_white(int x, int y, int nx, int ny, int find, bool from_blue, int ndir) {
    bool found = false;
    for (int j = 0; j < horse_position[x][y].size(); j++) {
        int num, dir;
        tie(num, dir) = horse_position[x][y][j];
        if (num == find) {
            if (from_blue) dir = ndir;
            found = true;
        }
        if (found) {
            horse_position[nx][ny].push_back(make_pair(num, dir));
            horse_position[x][y].erase(horse_position[x][y].begin() + j);
            horse_info[num] = make_tuple(nx, ny, dir);
            j--;
        }
    }
    if (horse_position[nx][ny].size() >= 4) return true;
    else return false;
}

bool next_red(int x, int y, int nx, int ny, int find, bool from_blue, int ndir) {
    bool found = false;
    vector<pair<int, int>> carrier;
    for (int j = 0; j < horse_position[x][y].size(); j++) {
        int num, dir;
        tie(num, dir) = horse_position[x][y][j];
        if (num == find) {
            if (from_blue) dir = ndir;
            found = true;
        }
        if (found) {
            carrier.push_back(make_pair(num, dir));
            horse_position[x][y].erase(horse_position[x][y].begin() + j);
            horse_info[num] = make_tuple(nx, ny, dir);
            j--;
        }
    }
    reverse(carrier.begin(), carrier.end());
    for (int j = 0; j < carrier.size(); j++) {
        int num, dir;
        tie(num, dir) = carrier[j];
        horse_position[nx][ny].push_back(make_pair(num, dir));
    }
    if (horse_position[nx][ny].size() >= 4) return true;
    else return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> k;
    
    vector<vector<int>> a(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    
    horse_position.resize(n, vector<vector<pair<int, int>>>(n));
    
    for (int i = 0; i < k; i++) {
        int x, y, dir;
        cin >> x >> y >> dir;
        x -= 1;
        y -= 1;
        dir -= 1;
        horse_info.push_back(make_tuple(x, y, dir));
        horse_position[x][y].push_back(make_pair(i, dir));
    }
    int test = 0;
    for (test = 1; test <= 1000; test++) {
        bool success = false;
        for (int i = 0; i < horse_info.size(); i++) {
            int x, y, dir;
            tie(x, y, dir) = horse_info[i];
            int nx = x + dx[dir], ny = y + dy[dir];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n || (a[nx][ny] == 2)) {
                if (dir % 2 == 0) dir += 1;
                else dir -= 1;
                nx = x + dx[dir];
                ny = y + dy[dir];
                horse_info[i] = make_tuple(x, y, dir);
                if (nx >= 0 && nx < n && ny >= 0 && ny < n && a[nx][ny] != 2) {
                    if (a[nx][ny] == 0) success = next_white(x, y, nx, ny, i, true, dir);
                    else success = next_red(x, y, nx, ny, i, true, dir);
                    if (success) break;
                }
                else {
                    for (int k = 0; k < horse_position[x][y].size(); k++) {
                        int num, ndir;
                        tie(num, ndir) = horse_position[x][y][k];
                        if (num == i) {
                            horse_position[x][y][k] = make_pair(num, dir);
                            break;
                        }
                    }
                }
            }
            else if (a[nx][ny] == 0) {
                success = next_white(x, y, nx, ny, i, false, 0);
                if (success) break;
            }
            else {
                success = next_red(x, y, nx, ny, i, false, 0);
                if (success) break;
            }
        }
        if (success) break;
    }
    if (test > 1000) cout << -1;
    else cout << test << endl;
    
    return 0;
}
