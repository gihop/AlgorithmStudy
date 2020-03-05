//
//  알약_4811.cpp
//  DP
//
//  Created by jiho park on 2020/03/05.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>

#define endl "\n"
using namespace std;

//dfs와 dp를 이용한 문제.

long long dp[31][31];//dp[one][half] one은 현재 알약 한 조각 갯수, half는 현재 알약 반 조각 갯수. 한 조각이 one개 있고 반 조각이 half개 있을 때 총 경우의 수를 의미.

long long solve(int one, int half){
    if(one == 0) return 1;//알약 한 조각이 없다면 모두 반 조각만 남아서 경우의 수는 1임.
    
    if(dp[one][half]!=-1)
        return dp[one][half];//이미 이 상태에서 나타낼 수 있는 경우의 수가 계산이 됐으므로 그대로 반환.
    
    long long n = solve(one-1, half+1);//알약 한 조각을 먹은 경우.
    if(half>0) n += solve(one, half-1);//알약 반 조각을 먹은 경우.
    
    dp[one][half]=n;
    
    return n;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    while(true){
        int n;
        cin >> n;
        if(n==0) break;
        
        memset(dp, -1, sizeof(dp));
        long long ans = solve(n, 0);
        cout << ans << endl;
    }
    
    return 0;
}
