#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

//시간초과가 발생했다.
//배열이 매우 크기 때문에 최적화를 최대한 해줘야 한다.

//처음에는 문제를 풀었을 때 모든 맵을 순환하는 것을 반복하면서 제거해야하는 모래성인지 확인했다.
//제거해야하는 모래성이면 따로 벡터에 넣어서 탐색이 1번 끝나면 벡터에 담긴 모래성 위치를 제거했다.
//이 작업을 계속 반복하면서 제거해야할 모래성을 찾지 못한다면 끝나도록 설계했다. 이는 시간초과를 발생시켰다.

//그 다음 방법으로 현재 맵에서 주위에 있는 바다 칸의 갯수를 세서 바다칸 갯수만큼 모래성 숫자를 뺐다.
//이러한 전처리 과정을 거쳤을 때, 0이 된 모래성을 큐에 넣고 bfs를 사용해서 큐에 담긴 위치 주변을
//1씩 깎아서 0이 된 모래성을 다시 큐에 넣는 것을 반복한다.
//이 방법도 시간초과가 발생했다.

//바로 위의 방법도 시간초과가 난 이유중 가장 큰 이유는 queue<tuple<int,int,int>>를 사용했는데
//tuple에 인자가 많아질수록 속도가 느리다. 되도록 pair가 좋다.
//pair를 사용하기 위해 bfs를 실행할 때,
//기존에 큐가 빌때까지 반복하는 것이 아닌 bfs를 실행시키는 시점에 큐에 담긴 사이즈 만큼 반복한다.
//이 사이즈는 현재 시간에 추가된 큐만큼만 반복하는 것이기 때문에,
//그 횟수만큼 돌린 후에 time을 증가시키고, 다시 size를 갱신시켜서 결국 빌 때 까지 반복한다.
//그 중간중간에 time을 늘림으로써 pair를 사용할 수 있었다.

//또한 전처리가 필요 없었다. 처음에 바다인 부분을 큐에 넣고 시작하면 전처리를 하지 않아도 된다.

//또한 불필요한 memset가 있었다. 맵을 계속 0으로 갱신할 필요가 없다. 어차피 입력을 받으니까.


//시간을 줄이기 위한 방법.
//scanf를 꼭 써야하는 상황이 아니면 cin, cout에 ios_base 방법과 "\n"을 사용한다.
//memset을 꼭 써야하는 상황인지 잘 확인한다.
//tuple보다 pair가 빠르다.
//tuple에 인수를 추가하면 더 느려진다.

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

int a[1000][1000];
int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int dy[] = { 1, 1, 0, -1, -1, -1, 0, 1 };

int main(){
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int test_case;
    int T;
    
    //freopen("input.txt", "r", stdin);

    cin >> T;
    
    for (test_case = 1; test_case <= T; ++test_case) {
        int n, m;

        cin >> n >> m;
        
        queue<pair<int, int>> q;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                char ch;
                cin >> ch;
                if (ch == '.') {
                    a[i][j] = 0;
                    q.emplace(i, j);
                }
                else {
                    a[i][j] = ch - '0';
                }
            }
        }
        
        int time = 0;
        int size = q.size();
        while (true) {
            while (size--) {
                int x, y;
                tie(x, y) = q.front();
                q.pop();
                for (int i = 0; i < 8; i++) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                    if (a[nx][ny] > 0) {
                        a[nx][ny] -= 1;
                        if (a[nx][ny] == 0) {
                            q.emplace(nx, ny);
                        }
                    }
                }
            }
            size = q.size();
            if (size == 0) break;
            time++;
        }
        
        cout << "#" << test_case << " " << time << "\n";
    }
    
    return 0;
}
