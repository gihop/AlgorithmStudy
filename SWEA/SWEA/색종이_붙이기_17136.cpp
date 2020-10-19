#include <iostream>
#include <vector>

using namespace std;

//색종이_붙이기_17136 문제 재시도.
//까다로운 구현 문제다.

vector<vector<int>> a(10, vector<int>(10, 0));
int ans = 101;

void go(vector<int> paper, vector<vector<int>> next, int count, int x) {
    if (next == a) {
        if (count < ans) ans = count;
        return;
    }
    else if (count >= ans) return;
    for (int i = x; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (a[i][j] == 1 && next[i][j] == 0) {
                if (paper[4] > 0 && i + 5 <= 10 && j + 5 <= 10) {
                    bool success = true;
                    for (int k = i; k < i + 5; k++) {
                        for (int l = j; l < j + 5; l++) {
                            if (a[k][l] != 1 || next[k][l] != 0) {
                                success = false;
                                break;
                            }
                        }
                        if (!success) break;
                    }
                    if (success) {
                        for (int k = i; k < i + 5; k++) {
                            for (int l = j; l < j + 5; l++) {
                                next[k][l] = 1;
                            }
                        }
                        paper[4] -= 1;
                        go(paper, next, count + 1, i);
                        paper[4] += 1;
                        for (int k = i; k < i + 5; k++) {
                            for (int l = j; l < j + 5; l++) {
                                next[k][l] = 0;
                            }
                        }
                    }
                }
                if (paper[3] > 0 && i + 4 <= 10 && j + 4 <= 10) {
                    bool success = true;
                    for (int k = i; k < i + 4; k++) {
                        for (int l = j; l < j + 4; l++) {
                            if (a[k][l] != 1 || next[k][l] != 0) {
                                success = false;
                                break;
                            }
                        }
                        if (!success) break;
                    }
                    if (success) {
                        for (int k = i; k < i + 4; k++) {
                            for (int l = j; l < j + 4; l++) {
                                next[k][l] = 1;
                            }
                        }
                        paper[3] -= 1;
                        go(paper, next, count + 1, i);
                        paper[3] += 1;
                        for (int k = i; k < i + 4; k++) {
                            for (int l = j; l < j + 4; l++) {
                                next[k][l] = 0;
                            }
                        }
                    }
                }
                if (paper[2] > 0 && i + 3 <= 10 && j + 3 <= 10) {
                    bool success = true;
                    for (int k = i; k < i + 3; k++) {
                        for (int l = j; l < j + 3; l++) {
                            if (a[k][l] != 1 || next[k][l] != 0) {
                                success = false;
                                break;
                            }
                        }
                        if (!success) break;
                    }
                    if (success) {
                        for (int k = i; k < i + 3; k++) {
                            for (int l = j; l < j + 3; l++) {
                                next[k][l] = 1;
                            }
                        }
                        paper[2] -= 1;
                        go(paper, next, count + 1, i);
                        paper[2] += 1;
                        for (int k = i; k < i + 3; k++) {
                            for (int l = j; l < j + 3; l++) {
                                next[k][l] = 0;
                            }
                        }
                    }
                }
                if (paper[1] > 0 && i + 2 <= 10 && j + 2 <= 10) {
                    bool success = true;
                    for (int k = i; k < i + 2; k++) {
                        for (int l = j; l < j + 2; l++) {
                            if (a[k][l] != 1 || next[k][l] != 0) {
                                success = false;
                                break;
                            }
                        }
                        if (!success) break;
                    }
                    if (success) {
                        for (int k = i; k < i + 2; k++) {
                            for (int l = j; l < j + 2; l++) {
                                next[k][l] = 1;
                            }
                        }
                        paper[1] -= 1;
                        go(paper, next, count + 1, i);
                        paper[1] += 1;
                        for (int k = i; k < i + 2; k++) {
                            for (int l = j; l < j + 2; l++) {
                                next[k][l] = 0;
                            }
                        }
                    }
                }
                if (paper[0] > 0 && i + 1 <= 10 && j + 1 <= 10) {
                    bool success = true;
                    for (int k = i; k < i + 1; k++) {
                        for (int l = j; l < j + 1; l++) {
                            if (a[k][l] != 1 || next[k][l] != 0) {
                                success = false;
                                break;
                            }
                        }
                        if (!success) break;
                    }
                    if (success) {
                        for (int k = i; k < i + 1; k++) {
                            for (int l = j; l < j + 1; l++) {
                                next[k][l] = 1;
                            }
                        }
                        paper[0] -= 1;
                        go(paper, next, count + 1, i);
                        paper[0] += 1;
                        for (int k = i; k < i + 1; k++) {
                            for (int l = j; l < j + 1; l++) {
                                next[k][l] = 0;
                            }
                        }
                    }
                }
                return;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> a[i][j];
        }
    }
    
    vector<int> paper(5, 5);
    vector<vector<int>> next(10, vector<int>(10, 0));
    go(paper, next, 0, 0);
    
    
    if (ans == 101) cout << -1 << endl;
    else cout << ans << endl;
    
    return 0;
}
