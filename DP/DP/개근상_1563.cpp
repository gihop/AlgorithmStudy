//
//  개근상_1563.cpp
//  DP
//
//  Created by jiho park on 2020/07/15.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>

using namespace std;

//오랜만에 풀어본 dp+dfs 문제.

int MOD=1000000;
int dp[1001][3][2];//dp[i][j][k]는 i일에 j번 연속 결석하고 k번 지각을 한 것을 의미한다.
int n;

int go(int days, int absent, int late){
    if(absent==3 || late==2) return 0;//기저 조건. 3번 연속 결석하거나 2번 지각한 경우.
    if(days==n) return 1;//개근인 경우.
    
    int &result = dp[days][absent][late];
    if(result!=-1) return result;//이미 방문한 조건인 경우.
    
    result = go(days+1, 0, late) + go(days+1, absent+1, late) + go(days+1, 0, late+1);//출석인 경우, 연속 결석인 경우, 지각인 경우.
    result %= MOD;//1000000으로 나눠준다.
    
    return result;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;
    
    memset(dp, -1, sizeof(dp));
    
    cout << go(0, 0, 0);
    
    return 0;
}
