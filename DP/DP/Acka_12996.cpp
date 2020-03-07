//
//  Acka_12996.cpp
//  DP
//
//  Created by jiho park on 2020/03/07.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>

#define endl "\n"
using namespace std;

long long dp[51][51][51][51];
int A,B,C;
int n;

long long go(int S, int a, int b, int c){
    if(S == n){
        if(a==A && b==B && c==C) return 1;
        else return 0;
    }
    if(a>A || b>B || c>C) return 0;
    if(dp[S][a][b][c]!=-1) return dp[S][a][b][c];//잘못 생각했던 부분. 3곡을 a,c,b가 부르고, c,a,b가 불렀을 때 b에서 이미 dp에 값이 있으므로 그냥 return을 생각했었음. 그럴게 아니라 값을 리턴하면 이미 간 상태이므로 다시 안가도 됨.
    long long num=0;
    num+=go(S+1, a+1, b, c);
    num+=go(S+1, a+1, b+1, c);
    num+=go(S+1, a+1, b+1, c+1);
    num+=go(S+1, a+1, b, c+1);
    num+=go(S+1, a, b+1, c);
    num+=go(S+1, a, b+1, c+1);
    num+=go(S+1, a, b, c+1);
    dp[S][a][b][c]=num%1000000007;//잘못 생각했던 부분. 여기서 num을 나눠주지 않으면 long long임에도 값을 넘어가서 터짐. 값이 14, 17이고 11나머지를 구한다고 했을 때, (14+17)%11만 가능하다고 생각했었는데 14%11 + 17%11도 결과가 같음. 그래서 여기서 이미 나머지 연산을 해줘도 된다.
    
    return dp[S][a][b][c];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    memset(dp, -1, sizeof(dp));
    
    cin >> n >> A >> B >> C;
    cout << go(0,0,0,0);

    return 0;
}
