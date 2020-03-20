//
//  선발_명단_3980.cpp
//  DP
//
//  Created by jiho park on 2020/03/23.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

#define endl "\n"
using namespace std;

//dp 문제인줄 알았는데 간단한 브루트포스 문제였다. 쉽게 풀렸다.

int a[11][11];
bool squad[11];
int tc;
int ans;

void go(int idx, int sum){
    if(idx>=11){//선수 11명을 다 선발한 경우.
        if(ans < sum) ans = sum;
        return;
    }
    
    for(int i=0; i<11; i++){
        if(!squad[i] && a[idx][i]>0){//i번째 포지션이 공석이고 idx번째 선수가 i번째 포지션에 적합한 경우.
            squad[i]=true;
            go(idx+1, sum+a[idx][i]);
            squad[i]=false;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> tc;
    
    while(tc--){
        for(int i=0; i<11; i++){
            for(int j=0; j<11; j++){
                cin >> a[i][j];
            }
        }
        go(0,0);
        cout << ans << endl;
        ans=0;
    }
    
    return 0;
}
