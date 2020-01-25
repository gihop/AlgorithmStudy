//
//  벽_부수고_이동하기2_14442.cpp
//  BFS
//
//  Created by jiho park on 2020/01/25.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

int n,m;
int dx[]={0, 1, 0, -1};
int dy[]={1, 0, -1, 0};
int ans;

void go(int x, int y, int k, int cnt, bool check[1000][1000], vector<string> v){
    if(x==n-1 && y==m-1 && ans > cnt){
        ans=cnt;
        return;
    }
    
    for(int i=0; i<4; i++){
        int nx, ny;
        nx = x+dx[i];
        ny = y+dy[i];
        if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
        if(check[nx][ny]) continue;
        if(v[nx][ny] == '1' && k>0){
            check[nx][ny]=true;
            go(nx, ny, k-1, cnt+1, check, v);
        }
        if(v[nx][ny] == '0'){
            check[nx][ny]=true;
            go(nx, ny, k, cnt+1, check, v);
        }
    }
}

int main(){
    int k;
    cin >> n >> m >> k;
    ans = n*m;
    vector<string> v(n);
    for(int i=0; i<n; i++){
        cin >> v[i];
    }
    bool check[1000][1000];
    memset(check, false, sizeof(check));
    go(0, 0, k, 1, check, v);
    
    if(ans != n*m)
        cout << ans;
    else
        cout << "-1";
    
    return 0;
}
