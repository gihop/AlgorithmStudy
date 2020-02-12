//
//  문자판_2186.cpp
//  BFS
//
//  Created by jiho park on 2020/02/12.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>
#include <string>
#include <cstring>


#define endl "\n"
using namespace std;

//https://yabmoons.tistory.com/194  - 참고
//bfs는 메모리 초과가 발생하고 dfs는 시간초과가 발생한다.
//이 문제는 dynamic programming을 합쳐서 구현해야 한다.
//dp[a][b][c] 배열에서 각 배열 원소는 (a,b)위치에서 c번째 원소를 찾을 때 도달할 수 있는 정답의 갯수를 가지고 있다.

char a[100][100];
int n,m,k;
string word;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};
int ans;
int dp[100][100][80];//dp[x][y][z]=s 의 뜻은 'ABCDE'라는 문자열을 만들고 싶을 때 (x,y)에 있는 원소에서 "ABCDE"의 z번째 원소로 찾고자 했을 경우 만들 수 있는 'ABCDE'의 경로는 s개이다. 초기값은 모두 -1을 갖고있으며 아직 탐색하지 않았다는 뜻을 갖고 있다. 탐색뒤에 답을 가질 수 없다면 0을 저장한다.

int go(int idx, int x, int y){
    if(dp[x][y][idx]!=-1) return dp[x][y][idx];//이미 탐색을 한 원소라면 바로 원소값을 반환한다. go함수가 중첩된 상황에서 반환이 된다면 이제껏 방문했던 모든 원소에 반환값이 더해진다. 즉 여기에 몇번째 원소를 찾으러 왔다면 가볼 것도 없이 반환값만큼의 경로 수를 가진다라는 뜻이다.
    if(idx == word.size()){//정답으로 가는 경로를 찾은 경우, 중첩된 go 합수에서 방문했던 모든 원소값에 1이 더해진다.
        return 1;
    }
    char next = word[idx];//찾아야 할 단어.
    dp[x][y][idx]=0;//처음 방문한 원소는 0으로 시작한다. 만약 정답에 맞는 경로를 찾지 못한다면 그대로 0이다.
    for(int i=0; i<4; i++){
        for(int j=1; j<=k; j++){
            int nx = x+(dx[i]*j);
            int ny = y+(dy[i]*j);
            if(nx<0 || nx>=n || ny<0 || ny>=m) break;
            if(a[nx][ny] == next){//다음에 찾아야 할 원소를 찾은 경우.
                dp[x][y][idx] += go(idx+1, nx, ny);//반환된 값을 원소에 더해준다.
            }
        }
    }
    return dp[x][y][idx];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m >> k;
    
    memset(dp, -1, sizeof(dp));
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> a[i][j];
    cin >> word;
    
    queue<tuple<int,int,string>> q;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(a[i][j]==word[0]){//찾고자 하는 단어의 첫 번째와 같은 경우.
                ans += go(1, i, j);//0번째 인덱스의 단어를 찾았으니 이제 1번째 인덱스의 원소를 찾아야 한다. 따라서 idx=1이다.
            }
        }
    }
    
    cout << ans;
    
    return 0;
}
