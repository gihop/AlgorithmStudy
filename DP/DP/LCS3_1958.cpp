//
//  LCS3_1958.cpp
//  DP
//
//  Created by jiho park on 2020/07/14.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//처음에 틀렸었다.
//그 이유는 else문에서 가장 큰 값을 찾아서 넣을 때 6가지를 검사하지 않고 3가지를 검사했기 때문이다.
//aeb
//acb
//adb
//가 입력되었을 때
//i,j,k가 1,1,0인 경우, dp[2][2][1]을 만드는데 ae, ac, a의 최장공통수열 a를 찾아야 한다.
//하지만 dp[i][j+1][k+1], dp[i+1][j][k+1], dp[i+1][j+1][k] 만으로 dp[1][1][1]을 포함할 수 없으므로 문제가 dp가 틀릴 수 밖에 없었다.
//이렇게 했을 때는 dp가 최장공통수열이 2가 아닌 1이 나온다.
//그래서 6가지 방법으로 검사를 해야한다.

int dp[101][101][101];

int Bigger(int x, int y, int z){
    if(x>y && x>z) return x;
    else if(y>x && y>z) return y;
    else return z;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    string a, b, c;
    
    cin >> a >> b >> c;
    
    for(int i=0; i<a.size(); i++){
        for(int j=0; j<b.size(); j++){
            for(int k=0; k<c.size(); k++){
                if(a[i]==b[j] && b[j]==c[k])
                    dp[i+1][j+1][k+1] = dp[i][j][k]+1;
                else
                    dp[i+1][j+1][k+1] = max(dp[i][j+1][k+1], max(dp[i+1][j][k+1], max(dp[i+1][j+1][k], max(dp[i+1][j][k], max(dp[i][j+1][k], dp[i][j][k+1])))));
            }
        }
    }
    cout << dp[a.size()][b.size()][c.size()];
    
    return 0;
}
