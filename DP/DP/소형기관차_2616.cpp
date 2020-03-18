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

int a[50001];
int dp[50001][3];
int n, m;
int ans;

int go(int idx, int train){
    if(train==3 || idx>=n){
        return 0;
    }
    int &sum = dp[idx][train];
    if(sum != -1) return sum;
    sum=0;
    
    if(idx + m-1 <= n)
        sum = max(go(idx+1, train), (a[idx+m-1]-a[idx-1]) + go(idx+m, train+1));
    
    return sum;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;
    
    for(int i=1; i<=n; i++){
        int tmp;
        cin >> tmp;
        a[i] = a[i-1]+tmp;
    }
    
    cin >> m;
    
    memset(dp, -1, sizeof(dp));
    
    cout << go(1,0) << endl;
    
    return 0;
}
