//
//  뮤탈리스크_12869.cpp
//  DP
//
//  Created by jiho park on 2020/03/07.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>

#define endl "\n"
using namespace std;

//처음에 dp를 bool type으로 했을 때 틀렸었다.
//dp를 int type으로 바꿔서 cnt 값을 저장했고, 이미 방문했던 dp에 도달했을 때 cnt 값이 더 적으면 값을 갱신하게 바꿨다.

int n;
int a[3];
int dp[61][61][61];
int ans=987654321;

void go(int cnt, int x, int y, int z){
    if(x<0) x=0;//음수인 경우 0으로 바꿔준다.
    if(y<0) y=0;
    if(z<0) z=0;
    if(x==0 && y==0 && z==0){
        if(cnt<ans)  ans = cnt;
        return;
    }
    if(dp[x][y][z] != -1 && cnt >= dp[x][y][z]) return;//이미 방문했는데 cnt값이 dp값보다 크거나 같은 경우.
    dp[x][y][z]=cnt;
    go(cnt+1, x-9, y-3, z-1);
    go(cnt+1, x-9, y-1, z-3);
    go(cnt+1, x-3, y-9, z-1);
    go(cnt+1, x-1, y-9, z-3);
    go(cnt+1, x-1, y-3, z-9);
    go(cnt+1, x-3, y-1, z-9);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    memset(dp, -1, sizeof(dp));
    
    cin >> n;
    for(int i=0; i<n; i++)
        cin >> a[i];
    
    go(0, a[0], a[1], a[2]);
    
    cout << ans;
    
    return 0;
}
