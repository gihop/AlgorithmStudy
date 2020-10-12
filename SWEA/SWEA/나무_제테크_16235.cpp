#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

//나무_제테크_16235 문제 복습.
//8개월전에는 못풀었던 것으로 기억하는데 한 번에 풀었다.

int n, m, year;
int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int dy[] = { 1, 1, 0, -1, -1, -1, 0, 1 };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m >> year;
    
    vector<vector<vector<int>>> trees(n, vector<vector<int>>(n));
    vector<vector<int>> a(n, vector<int>(n, 0));
    vector<vector<int>> nutrition(n, vector<int>(n, 5));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    
    for (int i = 0; i < m; i++) {
        int x, y, age;
        cin >> x >> y >> age;
        trees[x-1][y-1].push_back(age);
    }
    
    for (int i = 0; i < year; i++) {
        vector<tuple<int, int, int>> dead;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (trees[j][k].size() > 1) sort(trees[j][k].begin(), trees[j][k].end());
                int nut = nutrition[j][k];
                for (int l = 0; l < trees[j][k].size(); l++) {
                    if (nut >= trees[j][k][l]) {
                        nut -= trees[j][k][l];
                        trees[j][k][l]++;
                    }
                    else {
                        dead.push_back(make_tuple(j, k, trees[j][k][l]));
                        trees[j][k].erase(trees[j][k].begin() + l);
                        l--;
                    }
                }
                nutrition[j][k] = nut;
            }
        }
        
        for (int j = 0; j < dead.size(); j++) {
            int x, y, age;
            tie(x, y, age) = dead[j];
            nutrition[x][y] += age / 2;
        }
        
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < trees[j][k].size(); l++) {
                    if (trees[j][k][l] % 5 == 0) {
                        for (int dir = 0; dir < 8; dir++) {
                            int nx = j + dx[dir], ny = k + dy[dir];
                            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                            trees[nx][ny].push_back(1);
                        }
                    }
                }
            }
        }
        
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                nutrition[j][k] += a[j][k];
            }
        }
    }
    
    int answer = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            answer += trees[i][j].size();
        }
    }
    
    cout << answer << endl;
    
    return 0;
}
