#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <cstring>
#include <algorithm>

using namespace std;

//복잡한 구현 문제.

int n;
set<tuple<int, int, int, int>> s;
vector<vector<int>> a;
int boundary[21][21];
int answer = 987654321;

void go(int x, int y, int d1, int d2) {
    if (s.count(make_tuple(x, y, d1, d2)) == 0 && x + d1 + d2 <= n && 1 <= y - d1 && y - d1 < y && y + d2 <= n) {
        s.insert(make_tuple(x, y, d1, d2));
        memset(boundary, 0, sizeof(boundary));
        
        for (int i = 0; i <= d1; i++) {
            boundary[x + i][y - i] = 5;
            boundary[x + d2 + i][y + d2 - i] = 5;
        }
        
        for (int i = 0; i <= d2; i++) {
            boundary[x + i][y + i] = 5;
            boundary[x + d1 + i][y - d1 + i] = 5;
        }
        
        for (int i = 1; i <= n; i++) {
            bool found = false;
            for (int j = 1; j <= n; j++) {
                if (!found && boundary[i][j] == 5 && (i != x || j != y) && (i != x + d1 + d2 || j != y - d1 + d2)) found = true;
                else if (found && boundary[i][j] == 5) found = false;
                if (found) continue;
                if (boundary[i][j] == 5) continue;
                if (i >= 1 && i < x + d1 && 1 <= j && j <= y) boundary[i][j] = 1;
                else if (i >= 1 && i <= x + d2 && y < j && j <= n) boundary[i][j] = 2;
                else if (x + d1 <= i && i <= n && 1 <= j && j < y - d1 + d2) boundary[i][j] = 3;
                else if (x + d2 < i && i <= n && y - d1 + d2 <= j && j <= n) boundary[i][j] = 4;
            }
        }

        vector<int> sum(5, 0);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (boundary[i][j] == 1) sum[0] += a[i][j];
                else if (boundary[i][j] == 2) sum[1] += a[i][j];
                else if (boundary[i][j] == 3) sum[2] += a[i][j];
                else if (boundary[i][j] == 4) sum[3] += a[i][j];
                else sum[4] += a[i][j];
            }
        }
        int diff = *max_element(sum.begin(), sum.end()) - *min_element(sum.begin(), sum.end());
        if (diff < answer) answer = diff;
    }
    else return;
    go(x, y, d1 + 1, d2);
    go(x, y, d1, d2 + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;
    
    a.resize(n+1, vector<int>(n+1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    
    for (int i = 1; i <= n-2; i++) {
        for (int j = 2; j <= n-1; j++) {
            go(i, j, 1, 1);
        }
    }
    
    cout << answer << "\n";
    
    return 0;
}
