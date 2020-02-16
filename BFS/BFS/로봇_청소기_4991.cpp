//
//  로봇_청소기_4991.cpp
//  BFS
//
//  Created by jiho park on 2020/02/16.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>
#include <cstring>
#include <map>

#define endl "\n"
using namespace std;

//비트마스크로 푼 문제임.
//더러운 칸이 최대 10개로 제한되어 있고, 더러운 칸을 들릴 때마다 방문이 초기화가 되어야 한다.
//그래서 비트마스크를 사용해서 더러운 칸 별로 다른 방문 배열을 제공한다.

char a[20][20];
int d[20][20][1024];//2^10 이라서 1024.
int n,m;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    while(true){
        cin >> m >> n;
        if(n==0 && m==0) break;
        memset(d, 0, sizeof(d));
        int sx,sy,dirty=0;
        map<pair<int,int>,int> Map;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                cin >> a[i][j];
                if(a[i][j]=='o'){
                    sx=i;
                    sy=j;
                    a[i][j]='.';
                }else if(a[i][j]=='*'){
                    Map[make_pair(i,j)]=dirty;//더러운 칸의 순서를 매김.
                    dirty++;
                }
            }
        }
        int ans=1;
        for(int i=0; i<dirty; i++){//2^더러운칸개수-1.
            ans *= 2;
        }
        ans -= 1;
        queue<tuple<int,int,int>> q;
        q.emplace(sx, sy, 0);
        d[sx][sy][0]=1;
        bool found = false;
        while(!q.empty()){
            int x, y, cnt;
            tie(x,y,cnt) = q.front();
            q.pop();
            if(cnt == ans){//더러운 칸이 총 4곳이면 cnt가 1111(=15)이어야 모든 더러운 칸을 방문한 것.
                cout << d[x][y][cnt]-1 << endl;
                found = true;
                break;
            }
            for(int i=0; i<4; i++){
                int nx, ny;
                nx = x+dx[i];
                ny = y+dy[i];
                if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                if(d[nx][ny][cnt]>0) continue;
                if(a[nx][ny]=='x') continue;
                else if(a[nx][ny]=='.'){
                    q.emplace(nx,ny,cnt);
                    d[nx][ny][cnt] = d[x][y][cnt]+1;
                }else if(a[nx][ny]=='*'){
                    int num = Map[make_pair(nx, ny)];//맵에서 방문한 더러운 칸의 순서를 찾음.
                    int new_cnt = cnt | (1 << num);//순서만큼 1을 shift 해줌.
                    q.emplace(nx,ny,new_cnt);
                    d[nx][ny][new_cnt] = d[x][y][cnt]+1;
                }
            }
        }
        if(!found)//모든 더러운 칸을 방문하지 못한 경우.
            cout << -1 << endl;
    }
    
    return 0;
}
