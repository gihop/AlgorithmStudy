#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <map>

using namespace std;

//2 1 1 2 0 0
//1 1 2 1 3 1
//3 3 0 0 0 0
//이 상태에서 열을 검사하면 4,5번 열이 0으로 시작하는 경우가 있다.
//이런 경우들 때문에 100개 열과 행을 다 검사해야 한다.

int r, c, k;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> r >> c >> k;
    r -= 1;
    c -= 1;
    
    vector<vector<int>> a(100, vector<int>(100, 0));
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> a[i][j];
        }
    }
    
    int time = 0;
    int row = 3, col = 3;
    for (time = 0; time <= 100; time++) {
        if (a[r][c] == k) break;
        if (row >= col) {
            for (int i = 0; i < row; i++) {
                map<int, int> m;
                for (int j = 0; j < col; j++) {
                    if (a[i][j] > 0 && m.count(a[i][j]) == 0) m[a[i][j]] = 1;
                    else if(m.count(a[i][j]) > 0) m[a[i][j]]++;
                }
                vector<pair<int, int>> sorting;
                for (map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++) {
                    sorting.push_back(make_pair(iter->second, iter->first));
                }
                sort(sorting.begin(), sorting.end());
                for (int j = 0; j < 50; j++) {
                    if (sorting.size() > j) {
                        int count, num;
                        tie(count, num) = sorting[j];
                        a[i][j * 2] = num;
                        a[i][j * 2 + 1] = count;
                        if (j * 2 + 2 > col) col = j * 2 + 2;
                    }
                    else {
                        a[i][j * 2] = 0;
                        a[i][j * 2 + 1] = 0;
                    }
                }
            }
        }
        else {
            for (int i = 0; i < col; i++) {
                map<int, int> m;
                for (int j = 0; j < row; j++) {
                    if (a[j][i] > 0 && m.count(a[j][i]) == 0) m[a[j][i]] = 1;
                    else if(m.count(a[j][i]) > 0) m[a[j][i]]++;
                }
                vector<pair<int, int>> sorting;
                for (map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++) {
                    sorting.push_back(make_pair(iter->second, iter->first));
                }
                sort(sorting.begin(), sorting.end());
                int next_length = 0;
                for (int j = 0; j < 50; j++) {
                    if (sorting.size() > j) {
                        int count, num;
                        tie(count, num) = sorting[j];
                        a[j * 2][i] = num;
                        a[j * 2 + 1][i] = count;
                        if (j * 2 + 2 > row) row = j * 2 + 2;
                    }
                    else {
                        a[j * 2][i] = 0;
                        a[j * 2 + 1][i] = 0;
                    }
                }
            }
        }
    }
    
    if (time > 100) cout << -1 << endl;
    else cout << time << endl;
    
    return 0;
}
