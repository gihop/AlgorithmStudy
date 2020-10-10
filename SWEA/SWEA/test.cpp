#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

//복잡한 구현 문제.
//dfs를 이용해서 풀었다.

int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[] = { 0, -1, -1, -1, 0, 1, 1, 1 };

int Max = 0;

//현재 map 정보, fishes 정보, 상어의 위치와 방향, 현재 점수를 받는다.
//현재 상어의 위치에 있는 물고기를 잡아먹은 후, 물고기들이 이동을 한다.
//상어의 현재 위치와 방향에서 갈 수 있는 모든 곳을 dfs 탐색한다.
void go(vector<vector<pair<int,int>>> map, vector<tuple<int, int, int, int>> fishes, int x, int y, int dir, int score) {
    //현재 상어 위치에 있는 물고기의 정보를 갖고 온다.
    int num, shark_dir, shark_x, shark_y;
    tie(num, shark_dir, shark_x, shark_y) = fishes[map[x][y].first - 1];
    //잡아먹은 물고기의 정보를 0으로 바꾼다.
    fishes[map[x][y].first - 1] = make_tuple(0, 0, 0, 0);
    //현재 위치 물고기의 점수를 더한다.
    score += map[x][y].first;
    //맵에서 물고기의 정보를 지운다.
    map[x][y].first = 0;
    
    //남은 물고기들이 이동을 한다.
    for (int i = 0; i < 16; i++) {
        int fish_num, fish_dir, fish_x, fish_y;
        tie(fish_num, fish_dir, fish_x, fish_y) = fishes[i];
        if (fish_num == 0) continue;
        
        //모든 방향을 검사한다.
        for (int j = 0; j < 8; j++) {
            int nx = fish_x + dx[fish_dir], ny = fish_y + dy[fish_dir];
            
            //맵을 벗어나는 경우.
            if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) {
                fish_dir++;
                if (fish_dir >= 8) fish_dir = 0;
                continue;
            }
            
            //이동할 위치에 상어가 있는 경우.
            if (nx == shark_x && ny == shark_y) {
                fish_dir++;
                if (fish_dir >= 8) fish_dir = 0;
                continue;
            }
            
            //이동할 위치에 다른 물고기가 있는 경우 서로 위치를 바꾼다.
            if (map[nx][ny].first > 0) {
                int change_fish_num, change_fish_dir;
                tie(change_fish_num, change_fish_dir) = map[nx][ny];
                map[nx][ny] = make_pair(fish_num, fish_dir);
                map[fish_x][fish_y] = make_pair(change_fish_num, change_fish_dir);
                fishes[change_fish_num - 1] = make_tuple(change_fish_num, change_fish_dir, fish_x, fish_y);
                fishes[fish_num - 1] = make_tuple(fish_num, fish_dir, nx, ny);
            }
            
            //빈 공간인 경우.
            else {
                map[fish_x][fish_y].first = 0;
                map[nx][ny] = make_pair(fish_num, fish_dir);
                fishes[fish_num - 1] = make_tuple(fish_num, fish_dir, nx, ny);
            }
            break;
        }
    }
    
    bool found = false;
    
    for (int i = 1; i < 4; i++) {
        int nx = shark_x + (dx[shark_dir] * i), ny = shark_y + (dy[shark_dir] * i);
        if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) break;
        if (map[nx][ny].first > 0) {
            go(map, fishes, nx, ny, shark_dir, score);
            found = true;
        }
    }
    //상어가 이동할 곳을 못찾은 경우 집으로 돌아간다.
    if (!found) {
        if(score > Max) Max = score;
        return;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    vector<vector<pair<int,int>>> map(4, vector<pair<int,int>>(4, make_pair(0,0)));
    vector<tuple<int, int, int, int>> fishes;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int num, dir;
            cin >> num >> dir;
            map[i][j] = make_pair(num, dir-1);
            fishes.push_back(make_tuple(num, dir - 1, i, j));
        }
    }
    
    sort(fishes.begin(), fishes.end());

    go(map, fishes, 0, 0, 0, 0);
    
    cout << Max << endl;
    
    return 0;
}
