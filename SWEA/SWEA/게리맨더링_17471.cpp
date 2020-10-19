#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

//게리맨더링_17471 문제 재시도.
//까다로운 브루트포스 문제였다.

int n;
vector<vector<int>> graph;
vector<int> population;
vector<bool> divide;
set<string> s;
int ans = 987654321;

void go(int idx, int count) {
    if (count > 0 && count < n) {
        bool success = true;
        vector<int> a, b;
        string as = "", bs = "";
        int sumA = 0, sumB = 0;
        for (int i = 0; i < n; i++) {
            if (divide[i]) {
                a.push_back(i);
                as += to_string(i);
                sumA += population[i];
            }
            else {
                b.push_back(i);
                bs += to_string(i);
                sumB += population[i];
            }
        }
        
        if (s.count(as) != 0) success = false;
        else s.insert(as);
        if (s.count(bs) != 0) success = false;
        else s.insert(bs);
        
        if (success) {
            vector<bool> visitedA(a.size(), false);
            vector<bool> visitedB(b.size(), false);
            
            queue<int> q;
            q.emplace(a[0]);
            visitedA[0] = true;
            while (!q.empty()) {
                int x = q.front();
                q.pop();
                for (int i = 0; i < graph[x].size(); i++) {
                    int nx = graph[x][i];
                    for (int j = 0; j < a.size(); j++) {
                        if (a[j] == nx && !visitedA[j]) {
                            visitedA[j] = true;
                            q.emplace(nx);
                        }
                    }
                }
            }
            bool successA = true;
            for (int i = 0; i < visitedA.size(); i++) {
                if (!visitedA[i]) {
                    successA = false;
                    break;
                }
            }
            if (successA) {
                q.emplace(b[0]);
                visitedB[0] = true;
                while (!q.empty()) {
                    int x = q.front();
                    q.pop();
                    for (int i = 0; i < graph[x].size(); i++) {
                        int nx = graph[x][i];
                        for (int j = 0; j < b.size(); j++) {
                            if (b[j] == nx && !visitedB[j]) {
                                visitedB[j] = true;
                                q.emplace(nx);
                            }
                        }
                    }
                }
                bool successB = true;
                for (int i = 0; i < visitedB.size(); i++) {
                    if (!visitedB[i]) {
                        successB = false;
                        break;
                    }
                }
                if (successB) {
                    int diff = max(sumA, sumB) - min(sumA, sumB);
                    if (diff < ans) ans = diff;
                }
            }
        }
    }
    else if (count == n) return;
    for (int i = idx; i < n; i++) {
        if (divide[i]) continue;
        divide[i] = true;
        go(i, count + 1);
        divide[i] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;
    
    population.resize(n, 0);
    
    for (int i = 0; i < n; i++) {
        cin >> population[i];
    }
    
    graph.resize(n);
    divide.resize(n, false);
    
    for (int i = 0; i < n; i++) {
        int count;
        cin >> count;
        for (int j = 0; j < count; j++) {
            int num;
            cin >> num;
            graph[i].push_back(num - 1);
        }
    }
    
    go(0, 0);
    
    if (ans == 987654321) cout << -1 << "\n";
    else cout << ans << "\n";
    
    return 0;
}
