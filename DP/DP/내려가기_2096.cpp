//
//  내려가기_2096.cpp
//  DP
//
//  Created by jiho park on 2020/07/12.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int a[100000][3];
int dp[100000][3];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;
    
    for(int i=0; i<n; i++)
        cin >> a[i][0] >> a[i][1] >> a[i][2];
    
    for(int i=0; i<3; i++)
        dp[0][i] = a[0][i];
    
    for(int i=1; i<n; i++){
        if(dp[i-1][0]){
            if(dp[i][0]<dp[i-1][0]+a[i][0]) dp[i][0]=dp[i-1][0]+a[i][0];
            if(dp[i][1]<dp[i-1][0]+a[i][1]) dp[i][1]=dp[i-1][0]+a[i][1];
        }
        if(dp[i-1][1]){
            if(dp[i][0]<dp[i-1][1]+a[i][0]) dp[i][0]=dp[i-1][1]+a[i][0];
            if(dp[i][1]<dp[i-1][1]+a[i][1]) dp[i][1]=dp[i-1][1]+a[i][1];
            if(dp[i][2]<dp[i-1][1]+a[i][2]) dp[i][2]=dp[i-1][1]+a[i][2];
        }
        if(dp[i-1][2]){
            if(dp[i][1]<dp[i-1][2]+a[i][1]) dp[i][1]=dp[i-1][2]+a[i][1];
            if(dp[i][2]<dp[i-1][2]+a[i][2]) dp[i][2]=dp[i-1][2]+a[i][2];
        }
    }
    int Max;
    if(dp[n-1][0]>dp[n-1][1]) Max=dp[n-1][0];
    else Max = dp[n-1][1];
    if(Max<dp[n-1][2]) Max = dp[n-1][2];
    memset(dp, 0, sizeof(dp));
    for(int i=0; i<3; i++)
        dp[0][i] = a[0][i];
    for(int i=1; i<n; i++){
        dp[i][0]=dp[i-1][0]+a[i][0];
        dp[i][1]=dp[i-1][1]+a[i][1];
        dp[i][2]=dp[i-1][2]+a[i][2];
        if(dp[i][1]>dp[i-1][0]+a[i][1]) dp[i][1]=dp[i-1][0]+a[i][1];
        
        if(dp[i][0]>dp[i-1][1]+a[i][0]) dp[i][0]=dp[i-1][1]+a[i][0];
        if(dp[i][2]>dp[i-1][1]+a[i][2]) dp[i][2]=dp[i-1][1]+a[i][2];
        
        if(dp[i][1]>dp[i-1][2]+a[i][1]) dp[i][1]=dp[i-1][2]+a[i][1];
    }
    int Min;
    if(dp[n-1][0]>dp[n-1][1]) Min=dp[n-1][1];
    else Min = dp[n-1][0];
    if(Min>dp[n-1][2]) Min = dp[n-1][2];
    
    cout << Max << " " << Min << endl;

    return 0;
}
