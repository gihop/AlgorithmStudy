//
//  1학년_5557.cpp
//  DP
//
//  Created by jiho park on 2020/07/09.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

using namespace std;

//n개의 숫자가 입력됐을 때 연산의 값이 arr[n-1]과 같은지 확인하는 것이다.
//dp[i][j]는 i번째 연산까지 했을 때, 0<=j<=20 나올 수 있는 숫자의 경우의 수들을 의미한다.
//즉 dp[n-2][arr[n-1]]은 마지막의 전 연산인 n-2번째 까지 연산을 했을 때, 마지막숫자인 arr[n-1]이 나올 수 있는 모든 경우의 수를 의미한다.
//j는 이전 연산의 값을 의미한다. 어차피 j의 값은 0~20으로 제한되므로.
//j에 +-arr[i] 다음 연산을 했을 때 0~20 사이인지 확인한다.
//만약 입력이
//11
//8 3 2 4 8 7 2 4 0 8 8
//일 때를 생각해보자.
//꼭 다시 풀어보자.

int n;
int arr[100];
long long dp[100][21];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;
    
    for(int i=0; i<n; i++)
        cin >> arr[i];
    dp[0][arr[0]]=1;//0번째 연산을 했을 때 0번째 숫자가 나올 수 있는 경우의 수는 1이므로 초기값 설정.
    for(int i=1; i<n-1; i++){//1번째 연산부터 시작해서 마지막 전 연산까지 반복한다.
        for(int j=0; j<=20; j++){//값은 0~20까지만 인정되기 때문.
            if(j-arr[i]>=0) dp[i][j-arr[i]]+=dp[i-1][j];
            if(j+arr[i]<=20) dp[i][j+arr[i]]+=dp[i-1][j];
        }
    }
    cout << dp[n-2][arr[n-1]] << endl;
    
    return 0;
}
