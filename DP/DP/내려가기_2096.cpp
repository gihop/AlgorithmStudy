//
//  내려가기_2096.cpp
//  DP
//
//  Created by jiho park on 2020/07/12.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>

using namespace std;

//처음에는 dp 배열을 dp[100000][3] 크기로 해서 메모리 초과가 발생했다.
//이 문제의 메모리 제한이 4mb로 적기 때문이다.
//이를 해결하기 위해 dp[2][3]으로 바꿨다.
//dp배열을 채워나갈 때 2개의 행만 필요하고 나머지를 계속 저장하고 있을 필요가 없기 때문이다.

int n;
int a[100000][3];
int dp[2][3];

int bigger(int x, int y){ if(x>y) return x; return y; }
int smaller(int x, int y){ if(x>y) return y; return x; }

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
        dp[1][0] = a[i][0]+bigger(dp[0][0], dp[0][1]);
        dp[1][1] = a[i][1]+bigger(dp[0][0], bigger(dp[0][1], dp[0][2]));
        dp[1][2] = a[i][2]+bigger(dp[0][1], dp[0][2]);
        for(int j=0; j<3; j++){//이 부분에서 dp 배열을 2행만 쓰기 위해서 1행을 0행으로 땡긴다.
            dp[0][j] = dp[1][j];
            dp[1][j]=0;
        }
    }
    int Max = bigger(dp[0][0], bigger(dp[0][1],dp[0][2]));
    memset(dp, 0, sizeof(dp));
    
    for(int i=0; i<3; i++)
        dp[0][i] = a[0][i];
    for(int i=1; i<n; i++){
        dp[1][0]=a[i][0]+smaller(dp[0][0], dp[0][1]);
        dp[1][1]=a[i][1]+smaller(dp[0][0], smaller(dp[0][1], dp[0][2]));
        dp[1][2]=a[i][2]+smaller(dp[0][1], dp[0][2]);
        for(int j=0; j<3; j++){
            dp[0][j] = dp[1][j];
            dp[1][j]=0;
        }
    }
    int Min=smaller(dp[0][0], smaller(dp[0][1], dp[0][2]));
    
    cout << Max << " " << Min << endl;

    return 0;
}
