//
//  벽장문의_이동_2666.cpp
//  DP
//
//  Created by jiho park on 2020/07/22.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

//밑에 잘못 풀이가 있다.
//이러한 풀이 방식에 익숙해질 필요가 있다.
//밑에 잘못 풀이 처럼 조건이 3개인줄 알았는데 조건은 두개면 가능하다.

int dp[21][21][21];
int a[20];
int n, m;

int go(int x, int y, int idx){
    if(idx>=m) return 0;
    
    int &result = dp[x][y][idx];
    if(result != -1) return result;
    
    result = min(abs(a[idx]-x)+go(a[idx],y,idx+1), abs(a[idx]-y)+go(x,a[idx],idx+1));
    
    return result;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;
    
    int x, y;
    
    cin >> x >> y >> m;
    
    for(int i=0; i<m; i++)
        cin >> a[i];
    
    memset(dp, -1, sizeof(dp));
    
    cout << go(x, y, 0);
    
    return 0;
}

/* 잘못 푼 풀이.
 void go(int x, int y, int idx, int count){
    if(idx>=m) return;
    int target = a[idx];
 
    if(target <= x){
        int move = count + x - target;
        if(dp[idx]!=-1 && dp[idx]<move) return;
        dp[idx]=move;
        go(target, y, idx+1, move);
    }
    else if(target >= y){
        int move = count + target - y;
        if(dp[idx]!=-1 && dp[idx]<move) return;
        dp[idx]=move;
        go(x, target, idx+1, move);
    }
    else{
        int move1 = count + y - target, move2 = count + target - x;
        go(x, target, idx+1, move1);
        go(target, y, idx+1, move2);
        if((move1>move2 && dp[idx]>move2) || dp[idx]==-1) dp[idx]=move2;
        else if((move1<move2 && dp[idx]>move1) || dp[idx]==-1) dp[idx]=move1;
    }
 }
 */
