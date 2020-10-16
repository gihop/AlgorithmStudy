#include <iostream>
#include <vector>
#include <tuple>
#include <cstring>

using namespace std;

//문제에서 이미 말이 있는 곳은 가면 안된다는 부분을 보지못해서 틀렸었다.
//문제를 잘 읽자.

//visited를 벡터보다 배열로 하니까 더 빨라졌다.

vector<vector<int>> a = { {0,2,4,6,8,10}, {10,13,16,19,25,30}, {10,12,14,16,18,20},
    {20,22,24,25,30,35}, {20,22,24,26,28,30}, {30,28,27,26,25,30}, {30,32,34,36,38,40} };
vector<int> order(10, 0);
bool visited[7][6];
int Max = 0;

void go(vector<int> number) {
    if (number.size() == 10) {
        int sum = 0;
        vector<pair<int, int>> position(4, make_pair(0, 0));
        memset(visited, false, sizeof(visited));
        for (int idx = 0; idx < 10; idx++) {
            int next_horse = number[idx];
            int pre_x, pre_y;
            tie(pre_x, pre_y) = position[next_horse];
            int next = order[idx];
            if (pre_x == -1) return;
            int x = pre_x, y = pre_y;
            
            if (x == 0 && y == 5) {
                x = 1;
                y = 0;
            }
            else if (x == 2 && y == 5) {
                x = 3;
                y = 0;
            }
            else if (x == 4 && y == 5) {
                x = 5;
                y = 0;
            }
            
            y += next;
            
            if (x == 1 && y >= 4) {
                x = 3;
                y -= 1;
            }
            if (x == 5 && y >= 4) {
                x = 3;
                y -= 1;
            }
            if (x == 3 && y > 5) {
                x = 6;
                y -= 1;
            }
            if (x == 6 && y >= 6) {
                x = -1;
                y = -1;
            }
            else if (y > 5) {
                y -= 5;
                if (x == 0) {
                    x = 2;
                }
                else if (x == 2) {
                    x = 4;
                }
                else if (x == 4) {
                    x = 6;
                }
            }
            if (x != -1) {
                if (visited[x][y]) return;
                visited[x][y] = true;
            }
            visited[pre_x][pre_y] = false;
            position[next_horse] = make_pair(x, y);
            if (x != -1) sum += a[x][y];
        }
        if (sum > Max)
            Max = sum;
        return;
    }
    for (int i = 0; i < 4; i++) {
        number.push_back(i);
        go(number);
        number.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    for (int i = 0; i < 10; i++)
        cin >> order[i];
    vector<int> number;
    go(number);
    
    cout << Max << endl;
    
    return 0;
}
