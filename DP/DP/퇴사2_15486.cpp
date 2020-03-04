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

int DP[1500002];
int a[1500002][2];
int n;

void solve(){
    for(int i=1; i<=n; i++){
        int money = a[i][0];
        int day = a[i][1];
        if(day+i>n) continue;
        if(DP[day+i] < money+DP[i]) DP[day+i] = money+DP[i];
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;
    
    for(int i=1; i<=n; i++){
        cin >> a[i][0] >> a[i][1];
    }
    
    return 0;
}
