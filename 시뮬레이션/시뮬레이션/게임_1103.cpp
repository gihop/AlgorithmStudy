//
//  게임_1103.cpp
//  시뮬레이션
//
//  Created by jiho park on 2020/02/25.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>

#define endl "\n"
using namespace std;

//bfs로 풀기가 쉽지 않음.
//dfs와 dp를 이용해서 풀어야 함.
//이 문제에서 경로에 사이클이 생기면 -1을 출력해야하는데 bfs에서 사이클을 찾기가 쉽지 않다.
//6 7
//12HHHHH
//2214HHH
//H1HHHHH
//H4H9H2H
//HHHHHHH
//HHH2HHH
//bfs에서 방문한 곳을 또 방문하면 사이클이라고 생각해서 풀었었는데 이 경우에서 (3,1)에 씌여있는 4에 도착하면 사이클이 아니라 맵을 벗어나거나 구멍에 빠지게 되어있는데 bfs 방식대로 가면 두 번 방문하게 된다. 사이클이 아닌데도 사이클이라고 판단하게 된다.
//그래서 dfs와 dp를 같이 사용한다.
//check 배열은 현재 내가 지나온 경로에 한해서만 true로 해놓고 경로가 줄어들 때는 check도 false로 바꿔서 딱 지나온 발자취만 true가 되게 만든다.
//dp에는 해당 칸에서 출발했을 때 동전을 몇 번 움직이는지 저장하는데 먼저 해당칸에서 갈 수 있는 모든 방향을 조사하고 그 중에 가장 큰 값만 저장한다. 그 뒤로 다른 dfs경로에서 다시 그 칸에 도착했을 경우 dp값만 반환받는다.

int a[51][51];
int dp[51][51];
bool check[51][51];
int n, m;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int Bigger(int x, int y) { if(x>y) return x; else return y; }

int dfs(int x, int y){
    if(x<0 || x>=n || y<0 || y>=m || a[x][y]==0) return 0;//맵을 벗어나거나 구멍에 빠진 경우.
    if(check[x][y]){//현재 지나온 경로에서 똑같은 곳을 다시 방문한다면 사이클이 생겼다고 판단할 수 있음.
        cout << -1;
        exit(0);
    }
    if(dp[x][y] != -1) return dp[x][y];//이미 해당칸에서 출발했을 때 동전을 최대 몇번 움직일 수 있는지 조사가 끝난 칸임.
    
    check[x][y]=true;//경로에 들어온 칸이므로 방문 표시를 해둠.
    dp[x][y]=0;
    for(int i=0; i<4; i++){
        int nx, ny;
        nx = x+dx[i]*a[x][y];
        ny = y+dy[i]*a[x][y];
        dp[x][y] = Bigger(dp[x][y], dfs(nx,ny)+1);//이미 조사해온 dp값과 현재 조사해온 dfs값 중에 큰 값을 다시 dp값에 저장한다.
    }
    check[x][y]=false;//이 곳에 왔다는 것은 dfs방문을 끝내고 x,y칸을 벗어나 반환될 예정이기 때문에 해당 칸에 대한 방문 표시를 제거해야 함.
    
    return dp[x][y];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m;
    
    for(int i=0; i<n; i++){
        string s;
        cin >> s;
        for(int j=0; j<s.size(); j++){
            if(s[j]=='H') a[i][j]=0;
            else a[i][j] = s[j]-'0';
        }
    }
    
    memset(dp, -1, sizeof(dp));
    int ans = dfs(0,0);
    cout << ans;
    
    return 0;
}


//6 7
//12HHHHH
//2214HHH
//H1HHHHH
//H4H9H2H
//HHHHHHH
//HHH2HHH
//int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
//    cout.tie(NULL);
//
//    cin >> n >> m;
//
//    for(int i=0; i<n; i++){
//        for(int j=0; j<m; j++){
//            char ch;
//            cin >> ch;
//            if(ch == 'H') a[i][j]=0;
//            else a[i][j]=atoi(&ch);
//        }
//    }
//
//    queue<pair<int,int>> q;
//    q.emplace(0,0);
//    d[0][0]=0;
//    while(!q.empty()){
//        int x, y, num;
//        tie(x,y) = q.front();
//        q.pop();
//        num = a[x][y];
//        for(int i=0; i<4; i++){
//            int nx = x+dx[i]*num;
//            int ny = y+dy[i]*num;
//            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
//            if(d[nx][ny]>0 && a[nx][ny]!=-1 && check[nx][ny]){
//                cout << -1;
//                return 0;
//            }
//            if(a[nx][ny]==-1){
//                if(d[nx][ny] < d[x][y]+1)
//                    d[nx][ny] = d[x][y]+1;
//                continue;
//            }
//            d[nx][ny] = d[x][y]+1;
//            q.emplace(nx,ny);
//            check[x][y]=true;
//        }
//    }
//    int ans=0;
//    for(int i=0; i<n; i++){
//        for(int j=0; j<m; j++){
//            if(a[i][j] == -1 && ans < d[i][j])
//                ans = d[i][j];
//            else if(a[i][j] != -1 && ans < d[i][j]+1)
//                ans = d[i][j]+1;
//        }
//    }
//    cout << ans;
//
//    return 0;
//}
