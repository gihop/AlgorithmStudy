//
//  파일_합치기_11066.cpp
//  DP
//
//  Created by jiho park on 2020/03/09.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <deque>

#define endl "\n"
using namespace std;

int tc;
int n;
int a[501];
int dp[501];
deque<int> dq;

void go(int idx, int dpx){
    if(idx==n){
        
    }
    for(int i=idx; i<n-1; i++){
        
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> tc;
    
    while(tc--){
        cin >> n;
        for(int i=0; i<n; i++)
            cin >> a[i];
    }
    
    
    return 0;
}
