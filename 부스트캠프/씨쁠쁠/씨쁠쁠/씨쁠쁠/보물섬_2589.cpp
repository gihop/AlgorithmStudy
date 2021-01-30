//
//  main.cpp
//  씨쁠쁠
//
//  Created by jiho park on 2021/01/30.
//

#include <iostream>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;

char a[50][50];
int dist[50][50];
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n, m;
    int answer = 0;
    
    cin >> n >> m;
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> a[i][j];
        }
    }
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(a[i][j] == 'L'){
                memset(dist, -1, sizeof(dist));
                queue<tuple<int, int, int>> q;
                q.emplace(i, j, 0);
                dist[i][j] = 0;
                while(!q.empty()){
                    int x, y, now;
                    tie(x, y, now) = q.front();
                    q.pop();
                    for(int k=0; k<4; k++){
                        int nx = x + dx[k], ny = y + dy[k];
                        if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                        if(dist[nx][ny] >= 0 || a[nx][ny] == 'W') continue;
                        q.emplace(nx, ny, now + 1);
                        dist[nx][ny] = now+1;
                        if(now + 1 > answer)
                            answer = now + 1;
                    }
                }
            }
        }
    }
    cout << answer << "\n";
    
    return 0;
}
