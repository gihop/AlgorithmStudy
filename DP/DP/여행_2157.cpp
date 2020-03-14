//
//  여행_2157.cpp
//  DP
//
//  Created by jiho park on 2020/03/14.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cstring>

#define endl "\n"
using namespace std;

int dp[301][301];
int n,m,k;
vector<pair<int,int>> v[301];
int ans;

int go(int pre, int now, int sum, int cnt){
    if(cnt>m){
        dp[cnt][now]=0;
        return dp[cnt][now];
    }
    if(cnt<=m && now==n){
        dp[cnt][now]=sum;
        return dp[cnt][now];
    }
    
    if(dp[cnt][now]!=-1) return dp[cnt][now];
    int num=0;
    for(int i=0; i<v[now].size(); i++){
        int next, score;
        tie(next, score) = v[now][i];
        int nscore = go(now, next, score, cnt+1);
        if(nscore > num) num = nscore+sum;
    }
    dp[cnt][now]=num;
    
    return dp[cnt][now];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    memset(dp, -1, sizeof(dp));
    
    cin >> n >> m >> k;
    
    for(int i=0; i<k; i++){
        int x,y,score;
        cin >> x >> y >> score;
        if(x<y)
            v[x].push_back(make_pair(y,score));
    }
    cout << go(0,1,0,1);
    
    return 0;
}
