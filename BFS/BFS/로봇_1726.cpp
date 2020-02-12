//
//  로봇_1726.cpp
//  BFS
//
//  Created by jiho park on 2020/02/12.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>

#define endl "\n"
using namespace std;

//주석 참조

int a[100][100];
bool check[100][100][4];
int n,m;
int dx[]={0, 0, 1, -1};
int dy[]={1, -1, 0, 0};

int left_dir(int d){
    if(d==0) return 3;
    else if(d==1) return 2;
    else if(d==2) return 0;
    else return 1;
}

int right_dir(int d){
    if(d==0) return 2;
    else if(d==1) return 3;
    else if(d==2) return 1;
    else return 0;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> a[i][j];
    
    int sx,sy,sd,ex,ey,ed;
    cin >> sx >> sy >> sd;
    cin >> ex >> ey >> ed;
    
    queue<tuple<int,int,int,int>> q;
    q.emplace(sx-1,sy-1,sd-1,0);
    check[sx-1][sy-1][sd-1]=true;
    
    while(!q.empty()){
        int x,y,d,cnt;
        tie(x,y,d,cnt) = q.front();
        q.pop();
        if(x==ex-1 && y==ey-1 && d==ed-1){
            cout << cnt;
            return 0;
        }
        for(int i=0; i<3; i++){
            if(i==0){
                int nx,ny;
                for(int j=1; j<=3; j++){
                    nx = x+(dx[d]*j);
                    ny = y+(dy[d]*j);
                    if(nx<0 || nx>=n || ny<0 || ny>=m) break;//한 번 맵을 벗어나면 그다음 반복문도 무조건 벗어난다.
                    if(a[nx][ny]==1) break;//이 부분 때문에 틀렸었는데 이 부분 역시 continue가 아닌 break를 해줘야 한다. continue를 해주면 바로 앞에는 벽이 있고 그 다음에 벽이 없으면 벽을 건너뛰게 된다.
                    if(check[nx][ny][d]) continue;
                    check[nx][ny][d]=true;
                    q.emplace(nx,ny,d,cnt+1);
                }
            }else if(i==1){
                int nd = left_dir(d);
                if(check[x][y][nd]) continue;
                q.emplace(x,y,nd,cnt+1);
                check[x][y][nd]=true;
            }else{
                int nd = right_dir(d);
                if(check[x][y][nd]) continue;
                q.emplace(x,y,nd,cnt+1);
                check[x][y][nd]=true;

            }
        }
    }
    
    return 0;
}
