#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

//까다로운 구현 문제지만 잘 풀었다.
//내가 생각해도 정말 기가막히게 푼 것 같다.

//이 문제의 관건은 2칸으로 이뤄진 블록이 서로 하나의 블록으로 인식하게 하는게 가장 중요하다고 생각한다.
//설명을 하자면
//0 0 0 0
//0 1 1 0
//0 2 0 0
//0 3 3 4
//각 숫자는 블록이고 중력에 의해 떨어질 때, 1 1은 같은 한 블록이믈로 2에 의해 떨어지면 안된다.
//이 때 위와 같은 방법으로 모든 추가된 블록에 숫자를 증가시켜서 map에 저장시킨다면
//1이라는 블록이 하나로 이뤄진 블록인지, 두개라면 나머지 한 칸 블록은 어디에 있는지 찾아야 해서
//비효율적이라고 생각했다.
//그래서 map을 pair로 구성해서
//first가 0이면 빈칸, 1이면 블록.
//second는 나머지 한 칸의 위치를 dx, dy의 원소값을 넣어서 방향을 가리키도록 했다.
//즉 1 1 두 칸의 한 블록이 [][] 모양으로 누워 있을 때,
//pair의 값은 (1,0), (1,2) 로 저장한다.
//1
//1
//모양의 서있는 블록은 (1,1), (1,3)을 저장한다.
//한 칸 짜리 하나의 블록은 second의 값을 -1로 해서 1은 (1,-1)을 저장한다.

//이렇게 저장하고 두칸의 한 블록에서 한칸만 삭제될 때, 다른 하나의 블록의 위치를 찾고 second의 값을
//-1로 해준다.

//사소한 실수 하나를 했다.
//score를 올릴 때, match 함수에서 블록으로 이뤄진 줄을 찾을 때마다 증가시켜줘야 하는데
//예를들어 두줄을 한 함수에서 찾으면 +2를 해야하는데 반환받고 나서 +1을 해서 틀렸었다.

int n;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

int score = 0;

//초록색 보드에 중력을 작용시키는 함수.
void gravity_green(vector<vector<pair<int,int>>>& green) {
    bool moved = true;
    bool paired = false;
    while (moved) {
        moved = false;
        paired = false;
        for (int i = 0; i < green.size() - 1; i++) {
            for (int j = 0; j < green[i].size(); j++) {
                if (green[i][j].first > 0) {//블록이 있는 경우.
                    if (green[i][j].second == -1) {//한 칸 짜리 한 블록인 경우.
                        if (green[i + 1][j].first == 0) {
                            green[i + 1][j] = make_pair(1, -1);
                            green[i][j] = make_pair(0, 0);
                            moved = true;
                        }
                    }
                    else if (green[i][j].second == 0) {//두 칸 짜리 누워있는 블록인 경우.
                        int paired_x = i + dx[0], paired_y = j + dy[0];
                        if (green[i + 1][j].first == 0 && green[paired_x + 1][paired_y].first == 0) {
                            green[i + 1][j] = make_pair(1, 0);
                            green[i][j] = make_pair(0, 0);
                            green[paired_x + 1][paired_y] = make_pair(1, 2);
                            green[paired_x][paired_y] = make_pair(0, 0);
                            moved = true;
                        }
                    }
                    //두 칸 짜리 서있는 블록인 경우.
                    else if (green[i][j].second == 1 && i < green.size() - 2) {
                        int paired_x = i + dx[1], paired_y = j + dy[1];
                        if (green[paired_x + 1][paired_y].first == 0) {
                            green[paired_x + 1][paired_y] = make_pair(1, 3);
                            green[paired_x][paired_y] = make_pair(1, 1);
                            green[i][j] = make_pair(0, 0);
                            moved = true;
                        }
                    }
                }
            }
        }
    }
}

//파란색 블록에 중력을 작용시키는 함수.
void gravity_blue(vector<vector<pair<int, int>>>& blue) {
    bool moved = true;
    bool paired = false;
    while (moved) {
        moved = false;
        paired = false;
        for (int i = 0; i < blue[0].size() - 1; i++) {
            for (int j = 0; j < blue.size(); j++) {
                if (blue[j][i].first > 0) {
                    if (blue[j][i].second == -1) {
                        if (blue[j][i + 1].first == 0) {
                            blue[j][i + 1] = make_pair(1, -1);
                            blue[j][i] = make_pair(0, 0);
                            moved = true;
                        }
                    }
                    else if (blue[j][i].second == 0 && i < blue[0].size() - 2) {
                        int paired_x = j + dx[0], paired_y = i + dy[0];
                        if (blue[paired_x][paired_y + 1].first == 0) {
                            blue[j][i] = make_pair(0, 0);
                            blue[paired_x][paired_y + 1] = make_pair(1, 2);
                            blue[paired_x][paired_y] = make_pair(1, 0);
                            moved = true;
                        }
                    }
                    else if (blue[j][i].second == 1) {
                        int paired_x = j + dx[1], paired_y = i + dy[1];
                        if (blue[paired_x][paired_y + 1].first == 0 && blue[j][i + 1].first == 0) {
                            blue[paired_x][paired_y + 1] = make_pair(1, 3);
                            blue[paired_x][paired_y] = make_pair(0, 0);
                            blue[j][i] = make_pair(0, 0);
                            blue[j][i + 1] = make_pair(1, 1);
                            moved = true;
                        }
                    }
                }
            }
        }
    }
}

//초록색 보드에 매칭되는 줄을 찾는 함수.
bool green_match(vector<vector<pair<int, int>>>& green) {
    bool matched = false;
    for (int i = 0; i < green.size(); i++) {
        bool same = true;
        for (int j = 0; j < green[i].size(); j++) {
            if (green[i][j].first == 0) {
                same = false;
                break;
            }
        }
        
        if (same) {
            matched = true;
            score++;//score를 이곳에서 증가시켜야 한다.
            for (int j = 0; j < green[i].size(); j++) {
                if (green[i][j].second == -1) {
                    green[i][j] = make_pair(0, 0);
                }
                else {
                    int dir = green[i][j].second;
                    int nx = i + dx[dir], ny = j + dy[dir];
                    green[nx][ny].second = -1;
                    green[i][j] = make_pair(0, 0);
                }
            }
        }
    }
    
    return matched;
}

//파란색 보드에서 같은 줄을 찾는 함수.
bool blue_match(vector<vector<pair<int, int>>>& blue) {
    bool matched = false;
    for (int i = 0; i < blue[0].size(); i++) {
        bool same = true;
        for (int j = 0; j < blue.size(); j++) {
            if (blue[j][i].first == 0) {
                same = false;
                break;
            }
        }
        
        if (same) {
            matched = true;
            score++;
            for (int j = 0; j < blue.size(); j++) {
                if (blue[j][i].second == -1) {
                    blue[j][i] = make_pair(0, 0);
                }
                else {
                    int dir = blue[j][i].second;
                    int nx = j + dx[dir], ny = i + dy[dir];
                    blue[nx][ny].second = -1;
                    blue[j][i] = make_pair(0, 0);
                }
            }
        }
    }
    
    return matched;
}

//연한 초록색에 블록이 있다면 맨 바깥쪽 줄을 삭제하는 함수.
bool green_special_block(vector<vector<pair<int, int>>>& green) {
    int count = 0;
    bool removed = false;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < green[i].size(); j++) {
            if (green[i][j].first > 0) {
                count++;
                break;
            }
        }
    }
    if (count) {
        removed = true;
        for (int i = green.size() - 1; i > green.size() - 1 - count; i--) {
            for (int j = 0; j < green[i].size(); j++) {
                if (green[i][j].first > 0) {
                    if (green[i][j].second == -1) {
                        green[i][j] = make_pair(0, 0);
                    }
                    else {
                        int dir = green[i][j].second;
                        int nx = i + dx[dir], ny = j + dy[dir];
                        green[nx][ny].second = -1;
                        green[i][j] = make_pair(0, 0);
                    }
                }
            }
        }
    }
    return removed;
}

//연한 파란색 보드에 블록이 있다면 맨 바깥쪽 블록을 삭제하는 함수.
bool blue_special_block(vector<vector<pair<int, int>>>& blue) {
    int count = 0;
    bool removed = false;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < blue.size(); j++) {
            if (blue[j][i].first > 0) {
                count++;
                break;
            }
        }
    }
    if (count) {
        removed = true;
        for (int i = blue[0].size() - 1; i > blue[0].size() - 1 - count; i--) {
            for (int j = 0; j < blue.size(); j++) {
                if (blue[j][i].first > 0) {
                    if (blue[j][i].second == -1) {
                        blue[j][i] = make_pair(0, 0);
                    }
                    else {
                        int dir = blue[j][i].second;
                        int nx = j + dx[dir], ny = i + dy[dir];
                        blue[nx][ny].second = -1;
                        blue[j][i] = make_pair(0, 0);
                    }
                }
            }
        }
    }
    return removed;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    vector<vector<pair<int,int>>> blue(4, vector<pair<int,int>>(6, make_pair(0,0)));
    vector<vector<pair<int,int>>> green(6, vector<pair<int,int>>(4, make_pair(0,0)));
    
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1) {
            green[0][y] = make_pair(1, -1);
            blue[x][0] = make_pair(1, -1);
        }
        else if (t == 2) {
            green[0][y] = make_pair(1, 0);
            green[0][y + 1] = make_pair(1, 2);
            blue[x][0] = make_pair(1, 0);
            blue[x][1] = make_pair(1, 2);
        }
        else {
            green[0][y] = make_pair(1, 1);
            green[1][y] = make_pair(1, 3);
            blue[x][0] = make_pair(1, 1);
            blue[x + 1][0] = make_pair(1, 3);
        }
        gravity_green(green);
        while (true) {
            bool matched = green_match(green);
            if (matched) gravity_green(green);
            else break;
        }
        while (true) {
            bool special_block = green_special_block(green);
            if (special_block) gravity_green(green);
            else break;
        }

        gravity_blue(blue);
        while (true) {
            bool matched = blue_match(blue);
            if (matched) gravity_blue(blue);
            else break;
        }
        while (true) {
            bool special_block = blue_special_block(blue);
            if (special_block) gravity_blue(blue);
            else break;
        }
    }
    
    int block_count = 0;
    for (int i = 0; i < green.size(); i++) {
        for (int j = 0; j < green[i].size(); j++) {
            if (green[i][j].first > 0) block_count++;
        }
    }
    
    for (int i = 0; i < blue.size(); i++) {
        for (int j = 0; j < blue[i].size(); j++) {
            if (blue[i][j].first > 0) block_count++;
        }
    }
    
    cout << score << endl;
    cout << block_count << endl;
    
    return 0;
}
