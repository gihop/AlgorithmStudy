//
//  소형기관차_2616.cpp
//  DP
//
//  Created by jiho park on 2020/03/18.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <cstring>

#define endl "\n"
using namespace std;

int a[50000];
int dp[50000][4];
int n, m;
int ans;

int go(int idx, int train, int cnt){
    if((cnt==m && train==3) || (idx==n)){
        return 0;
    }
    int num=0, tmp=0;
    
    if(cnt==m)
        tmp = go(idx+1, train+1, 1);
    else
        tmp = go(idx+1, train, cnt+1);
    if(tmp > num) num = tmp;
    tmp = go(idx+1, 0, 1);
    
    if(tmp > num) num = tmp;
    
    return dp[idx][train];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;
    
    for(int i=0; i<n; i++){
        cin >> a[i];
    }
    
    cin >> m;
    
    
    
    return 0;
}
