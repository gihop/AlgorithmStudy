//
//  알파벳_1987.cpp
//  DFS
//
//  Created by jiho park on 2020/02/29.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

#define endl "\n"
using namespace std;

//dfs와 백트래킹의 기본 문제.

int n,m;
char a[20][20];
bool check[26];//현재 지나온 경로에서 만난 알파벳을 저장하는 배열.
int ans;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};

void dfs(int x, int y, int cnt){
    if(x<0 || x>=n || y<0 || y>=m || check[a[x][y]-'A']) return;//맵을 벗어나거나 이미 만났던 알파벳인 경우.
    
    check[a[x][y]-'A']=true;//현재 알파벳에 대해 방문 표시 해줌.
    if(ans < cnt) ans = cnt;
    for(int i=0; i<4; i++){
        int nx,ny;
        nx = x+dx[i];
        ny = y+dy[i];
        dfs(nx, ny, cnt+1);
    }
    check[a[x][y]-'A']=false;//백트래킹. (x,y)를 벗어나기 때문에 방문 해제해야함.
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m;
    
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> a[i][j];
    
    dfs(0,0,1);
    
    cout << ans;
    
    return 0;
}
