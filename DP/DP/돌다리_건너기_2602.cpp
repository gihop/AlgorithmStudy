//
//  돌다리_건너기_2602.cpp
//  DP
//
//  Created by jiho park on 2020/07/16.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

//dp 구조만 설계할 수 있다면 쉬운 문제.

long long dp[100][20][2]; //dp[n][m][k]는 현재 n번째 돌다리에서 두루마리의 m번째 칸 문자를 찾고 있으며, k는 천사의 돌다리와 악마의 돌다리를 구분한다.
string order;
string a,b;

long long go(int now, int find, int angel){
    if(now == a.size() && find==order.size()) return 1;//돌다리를 끝까지 다 건넜고 두루마리의 문자를 모두 찾았다.
    else if(now == a.size()) return 0;//돌다리를 다 건넜으나 두루마리 문자를 모두 못찾은 경우.
    
    long long &result = dp[now][find][angel];
    
    if(result != -1) return result;//이미 방문한 상태인 경우.
    
    if(angel){
        result = go(now+1, find, 1);
        if(order[find] == a[now]) result += go(now+1, find+1, 0);//경우의 수를 모두 더해주어야 한다.
        
    }
    else{
        result =  go(now+1, find, 0);
        if(order[find] == b[now]) result += go(now+1, find+1, 1);
    }
    
    return result;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> order;
    cin >> a >> b;
    
    memset(dp, -1, sizeof(dp));
    
    cout << go(0, 0, true) + go(0, 0, false) << endl;//천사의 돌다리, 악마의 돌다리 각각 시작.
    
    return 0;
}
