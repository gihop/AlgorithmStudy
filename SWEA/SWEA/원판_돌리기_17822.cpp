#include <iostream>
#include <vector>
#include <set>

using namespace std;

//밑에 실수한 부분을 주석으로 표시했다.
//x += x; 이렇게 해서 틀렸다.
//정말 어이없는 실수이고 시험 때 이런 실수를 해서는 안된다.

int n, m, t;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m >> t;
    
    vector<vector<int>> a(n, vector<int>(m, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    
    for (int i = 0; i < t; i++) {
        int x, d, k;
        cin >> x >> d >> k;
        int temp_x = x;
        while (true) {
            if (x <= n) {
                vector<int> spin(m, 0);
                if (d == 0) {
                    for (int idx = m - k; idx < 2 * m - k; idx++) {
                        spin[idx - m + k] = a[x - 1][idx % m];
                    }
                    a[x - 1] = spin;
                }
                else {
                    for (int idx = k; idx < k + m; idx++) {
                        spin[idx - k] = a[x - 1][idx % m];
                    }
                    a[x - 1] = spin;
                }
            }
            else break;
            x += temp_x;//*****바로 이 부분*****
        }
        
        int sum = 0, count = 0;
        vector<pair<int, int>> same;
        set<pair<int, int>> s;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                if (a[j][k] == 0) continue;
                sum += a[j][k];
                count++;
                int &left = a[j][(k - 1 + m) % m];
                int &right = a[j][(k + 1) % m];
                if (left == a[j][k]) {
                    if (s.count(make_pair(j, k)) == 0) {
                        s.insert(make_pair(j, k));
                        same.push_back(make_pair(j, k));
                    }
                }
                if (right == a[j][k]) {
                    if (s.count(make_pair(j, k)) == 0) {
                        s.insert(make_pair(j, k));
                        same.push_back(make_pair(j, k));
                    }
                }
                if (j > 0) {
                    int& front = a[j - 1][k];
                    if (front == a[j][k]) {
                        if (s.count(make_pair(j, k)) == 0) {
                            s.insert(make_pair(j, k));
                            same.push_back(make_pair(j, k));
                        }
                    }
                }
                if (j < n - 1) {
                    int& back = a[j + 1][k];
                    if (back == a[j][k]) {
                        if (s.count(make_pair(j, k)) == 0) {
                            s.insert(make_pair(j, k));
                            same.push_back(make_pair(j, k));
                        }
                    }
                }
            }
        }
        if (same.size() == 0) {
            double avg = (double)sum / count;
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < m; k++) {
                    if (a[j][k] == 0) continue;
                    if (a[j][k] > avg) a[j][k] -= 1;
                    else if (a[j][k] < avg) a[j][k] += 1;
                }
            }
        }
        else {
            for (int j = 0; j<same.size(); j++) {
                a[same[j].first][same[j].second] = 0;
            }
        }
    }
    
    int answer = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            answer += a[i][j];
        }
    }
    cout << answer << "\n";
    
    return 0;
}
