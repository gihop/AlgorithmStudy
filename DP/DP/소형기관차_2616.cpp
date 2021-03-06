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

//꼭 다시 풀어봐야하는 문제.

int a[50001];
int dp[50001][3];
int n, m;
int ans;

int go(int idx, int train){
    if(train==3 || idx>=n) return 0; //기저 사례: train은 0,1,2 번호 밖에 없다. idx도 n보다 커지면 끝까지 간 것을 의미한다.
    
    int &sum = dp[idx][train];
    if(sum != -1) return sum;
    sum=0;
    
    if(idx + m-1 <= n)//열차 번호 idx를 포함해서 m개의 열차를 끌고 갈 수 있는 경우.
        sum = max(go(idx+1, train), (a[idx+m-1]-a[idx-1]) + go(idx+m, train+1));//현재 열차를 끌고 가지 않는 경우(go(idx+1, train))과 현재 열차를 포함한 m개의 열차를 끌고 갔을 경우에서 크기를 비교한다.
    
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
