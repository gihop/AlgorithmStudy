//
//  LCS_9251.cpp
//  DP
//
//  Created by jiho park on 2020/07/08.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <string>

//오랜만에 푸는 dp 문제라서 감을 잡기 어려웠다.
//꼭 다시 풀어봐야하는 문제.
//http://melonicedlatte.com/algorithm/2018/03/15/181550.html
//위 링크를 참고해서 이해했다.

using namespace std;

int dp[1001][1001];

int bigger(int a, int b) { if(a>b) return a; return b; }

void solution(string a, string b){
    for(int i=0; i<a.size(); i++){
        for(int j=0; j<b.size(); j++){
            if(a[i]==b[j]) dp[i+1][j+1]=dp[i][j]+1;
            else dp[i+1][j+1] = bigger(dp[i][j+1], dp[i+1][j]);
        }
    }
    cout << dp[a.size()][b.size()] << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string a, b;

    cin >> a >> b;

    solution(a, b);

    return 0;
}
