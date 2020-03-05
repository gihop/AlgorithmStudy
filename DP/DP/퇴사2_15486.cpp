//
//  퇴사2_15486.cpp
//  DP
//
//  Created by jiho park on 2020/03/03.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <algorithm>

#define endl "\n"
using namespace std;

//dp 시작.

int DP[1500002];//DP[n]은 n일 전까지 일했을 때 받을 수 있는 최대 돈을 의미함.
int a[1500002][2];
int n;
int ans;

void solve(){
    int currentMax=0;//이 문제에서 핵심.
    for(int i=1; i<=n+1; i++){
        int money = a[i][1];//오늘 잡혀있는 상담을 했을 때 받을 수 있는 금액.
        int day = a[i][0];//오늘 잡혀있는 상담이 걸리는 일 수.
        currentMax = max(DP[i], currentMax);//만약 이 부분이 없다면?
        //3 1 1 2 1 -> 걸리는 일 수.
        //9 0 0 1 5 -> 받을 수 있는 금액.
        //위의 예를 보았을 때, 1일과 5일 째 일을 했을 때 가장 큰 금액을 벌 수 있다.
        //currentMax가 없다면, 5일 째 dp[i]=0이기 때문에 0+5가 된다.
        //첫날에 벌어서 4일날 벌 수 있는 돈이 9부터 시작하기 때문에 currentMax를 갱신시켜야 한다.
        //3 3 1 2 1
        //8 9 0 1 5
        //이 경우 5일차에 dp[i]=9, currentMax가 8인데 dp[i]가 더 크므로 max함수가 필요하다.
        if(day+i>n+1) continue;
        if(DP[day+i] < money+currentMax)
            DP[day+i] = money+currentMax;
    }
    ans = currentMax;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;
    
    for(int i=1; i<=n; i++){
        cin >> a[i][0] >> a[i][1];
    }
    
    solve();
    
    cout << ans;
    
    return 0;
}
