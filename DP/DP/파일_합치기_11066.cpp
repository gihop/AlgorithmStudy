//
//  파일_합치기_11066.cpp
//  DP
//
//  Created by jiho park on 2020/03/09.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <algorithm>

#define endl "\n"
using namespace std;

//https://m.blog.naver.com/tjdwns0920/221135677693 참고.
//꼭 다시 봐야하는 어려운 문제였다.
//인접한 파일끼리만 묶어야 한다.

int tc;
int n;
int a[501];
int dp[501][501];//dp[i][j]는 i에서 j파일까지 더하는데 최소 비용.
int sum[501];
int INF=0x3f3f3f3f;

int go(int start, int last){//파일이 두 개 혹은 한 개가 되도록 계속 쪼갠다.
    if(dp[start][last]!=INF) return dp[start][last];
    
    if(start==last){//파일이 한 개인 경우. 파일이 한 개일때는 더할 파일이 없으므로 0이다.
        dp[start][last]=0;
        return dp[start][last];
    }
    
    if(start+1 == last){//파일이 두 개인 경우.
        dp[start][last] = a[start]+a[last];
        return dp[start][last];
    }
    
    for(int mid = start; mid<last; mid++){
        //start가 1, last가 4일 때, 이 반복문은
        //{1}, {2,3,4}
        //{1,2}, {2,3}
        //{1,2,3}, {4} 로 쪼갠다.
        int left = go(start, mid);
        int right = go(mid+1, last);
        dp[start][last] = min(dp[start][last], left+right);
    }
    
    return dp[start][last] + sum[last] - sum[start-1];//예를 들어 start가 2, last가 4인 {2,3,4}를 합치는데 필요한 최소비용을 구했을 때, 마지막으로 2,3,4의 누적합을 더해줘야 하는데, 누적합인 sum[4]에는 sum[1]의 값도 포함되어있으므로 sum[start-1]을 빼줘야 한다.
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> tc;
    
    while(tc--){
        cin >> n;
        memset(dp, 0x3f, sizeof(dp));//memset은 0xABABABAB형태로 실행이 된다. 따라서 0,-1이 아닌 큰 수로 초기화 하고 싶을 때, 0x3f로 초기화를 하면 0x3f3f3f3f로 초기화가 된다. 이 문제의 경우 큰 수로 배열을 초기화를 해야해서 이렇게 사용했다.
        for(int i=1; i<=n; i++){
            cin >> a[i];
            sum[i] = sum[i-1]+a[i];//누적합을 미리 저장을 해놓는다.
        }
        cout << go(1,n) << endl;
    }
    
    return 0;
}
