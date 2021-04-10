#include <iostream>
#include <vector>

using namespace std;

int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };

bool check_out_of_range(int n, int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < n) return true;
    else return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> a(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    
    int answer = 0;
    int move = 1;
    bool done = false;
    int x = n / 2, y = n / 2;

    while (true) {
        for (int i = 0; i < 4; i++) {
            if (i == 2) move++;
            for (int j = 0; j < move; j++) {
                a[x][y] = 0;
                x += dx[i];
                y += dy[i];
                
                int sand = a[x][y];
                a[x][y] = 0;

                int five = (float)sand * 0.05;
                int ten = (float)sand * 0.1;
                int one = (float)sand * 0.01;
                int two = (float)sand * 0.02;
                int seven = (float)sand * 0.07;
                int alpha = sand - (ten * 2) - (seven * 2) - five - (two * 2) - (one * 2);
                
                int nx = x - dx[i], ny = y - dy[i];
                if (check_out_of_range(n, nx + dx[(i + 3) % 4], ny + dy[(i + 3) % 4]))
                    a[nx + dx[(i + 3) % 4]][ny + dy[(i + 3) % 4]] += one;
                else answer += one;
                if (check_out_of_range(n, nx + dx[(i + 1) % 4], ny + dy[(i + 1) % 4]))
                    a[nx + dx[(i + 1) % 4]][ny + dy[(i + 1) % 4]] += one;
                else answer += one;
                if (check_out_of_range(n, x + dx[(i + 3) % 4], y + dy[(i + 3) % 4]))
                    a[x + dx[(i + 3) % 4]][y + dy[(i + 3) % 4]] += seven;
                else answer += seven;
                if (check_out_of_range(n, x + dx[(i + 1) % 4], y + dy[(i + 1) % 4]))
                    a[x + dx[(i + 1) % 4]][y + dy[(i + 1) % 4]] += seven;
                else answer += seven;
                if (check_out_of_range(n, x + (dx[(i + 3) % 4] * 2), y + (dy[(i + 3) % 4] * 2)))
                    a[x + (dx[(i + 3) % 4] * 2)][y + (dy[(i + 3) % 4] * 2)] += two;
                else answer += two;
                if (check_out_of_range(n, x + (dx[(i + 1) % 4] * 2), y + (dy[(i + 1) % 4] * 2)))
                    a[x + (dx[(i + 1) % 4] * 2)][y + (dy[(i + 1) % 4] * 2)] += two;
                else answer += two;
                nx += (dx[i] * 2);
                ny += (dy[i] * 2);
                if (check_out_of_range(n, nx + dx[(i + 3) % 4], ny + dy[(i + 3) % 4]))
                    a[nx + dx[(i + 3) % 4]][ny + dy[(i + 3) % 4]] += ten;
                else answer += ten;
                if (check_out_of_range(n, nx + dx[(i + 1) % 4], ny + dy[(i + 1) % 4]))
                    a[nx + dx[(i + 1) % 4]][ny + dy[(i + 1) % 4]] += ten;
                else answer += ten;
                if (check_out_of_range(n, nx + dx[i], ny + dy[i]))
                    a[nx + dx[i]][ny + dy[i]] += five;
                else answer += five;
                if (check_out_of_range(n, nx, ny))
                    a[nx][ny] += alpha;
                else answer += alpha;
                if (x == 0 && y == 0) {
                    done = true;
                    break;
                }
            }
            if (done) break;
        }
        if (done) break;
        move++;
    }
    cout << answer;

    return 0;
}
