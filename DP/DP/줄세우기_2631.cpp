//
//  줄세우기.cpp
//  DP
//
//  Created by jiho park on 2020/07/13.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

//푸는 방법을 찾아내기 어려웠다.
//간단한 방법이 존재했다.
//최장증가수열을 찾으면된다.
//문제에서의
//3 7 5 2 6 1 4
//에서 최장증가수열은 3 5 6 이다.
//최장증가수열을 제외한 나머지 숫자들을 제자리에 넣으면 그것이 옮기는데 필요한 최소수이다.
//최장증가수열을 구하는 법은 순서대로
//3인경우 본인이 최장수열 1이고
//7일때 본인보다 앞에 있는 숫자들 중에 본인보다 작은 숫자를 찾는다.
//그 중에 dp값이 높은 값에 1을 더해서 dp값을 구한다.
int a[200];
int dp[200];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n;
    
    cin >> n;
    
    for(int i=0; i<n; i++)
        cin >> a[i];
    
    for(int i=0; i<n; i++){
        dp[i]=1;
        for(int j=0; j<i; j++){
            if(a[i]>a[j] && dp[i]<dp[j]+1)
                dp[i] = dp[j]+1;
        }
    }
    int Max=0;
    for(int i=0; i<n; i++)
        if(dp[i]>Max) Max = dp[i];
    
    cout << n-Max;
    
    return 0;
}
