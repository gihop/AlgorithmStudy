//
//  반도체_설계_2352.cpp
//  DP
//
//  Created by jiho park on 2020/07/20.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <algorithm>

using namespace std;

//LIS(Longest Increasing Subsequence) 문제.
//최대로 겹치지 않고 포트를 연결하려면 입력되는 포트 번호의 최장증가수열을 찾으면 된다.
//즉 입력이
//6
//4 2 6 3 1 5 이면
//2 3 5를 찾으면 된다.
//이 코드로 했을 때 2 3 5 가 아닌, 1 3 5를 찾게되는데 이는 선이 겹치기도 한다.
//dp에 들어가는 숫자들은 답과 전혀 연관이 없다는 것을 주의해야 한다.
//몸소 와닿지는 않아서 그냥 외워야 할 것 같다.
//초기값 4를 저장하고, 차례로 입력이 왔을 때 2가 입력이 오면
//dp의 가장 큰 값이 4인데, 입력인 2가 4보다 작으므로 dp 배열에서 4보다 같거나 큰숫자를 가장 앞 인덱스에서 찾는다.
//dp[1]=2가 되고, 6이 왔을 때, dp의 가장 큰 값인 2보다 입력인 6이 더 크므로 dp[2]=6으로 그대로 저장한다.
//이러한 방식으로 현재 갖고 있는 숫자보다 큰 값이면 그대로 저장하고, 작은 값이면 해당 위치에 맞는 인덱스를 찾아 저장한다.

int a[40001], dp[40001];
int n;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;
    
    for(int i=1; i<=n; i++)
        cin >> a[i];
    
    int len=1;
    
    dp[len] = a[1]; //초기값 설정
    
    for (int i = 2; i <= n; i++) {
        if (dp[len] < a[i]) {
            dp[++len] = a[i];
        }
        else {
            int val = lower_bound(dp + 1, dp + len + 1, a[i]) - dp;//dp배열은 우선 오름차순으로 정렬이 되어있다. dp 배열안에 a[i] 값보다 크거나 작은 값 중 가장 인덱스가 작은 값을 찾아낸다. 이 과정은 이분 탐색으로 이루어진다.
            dp[val] = a[i];
        }
    }
    
    cout << len;
    
    return 0;
}
