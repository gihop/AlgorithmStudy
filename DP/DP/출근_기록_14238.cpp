//
//  출근_기록_14238.cpp
//  DP
//
//  Created by jiho park on 2020/03/06.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <string>

#define endl "\n"
using namespace std;

//dp를 왜 써야하는지 계속 의문이였음. dfs로만 풀 수 있었다고 착각함.
//현재 코드에서 dp배열만 없애면 dfs임.
//dp가 왜 필요하냐면
//CAAACA 의 순열이 있다고 가정하자.
//여기서 만약 CAAACA순서로 검사를 했을 때
//CAAA CA
//ACAA CA
//띄어쓰기한 부분의 시점에서 A를 사용한 횟수, C를 사용한 횟수, 뒤에 문자, 뒤에뒤에 문자 상태가 같다.
//그래서 띄어쓰기 뒤의 결과도 항상 같다.
//그렇기 때문에 A,B,C를 사용한 횟수, 뒤의 문자, 뒤에뒤에 문자 상태를 dp로 저장해야한다.
//여기선 문장의 길이, A,B를 사용한 횟수로 했다. A,B와 문장의 길이를 알면 C를 알 수 있으므로 둘이 어차피 똑같다.

bool dp[51][51][51][3][3];//문장의 길이, A,B를 사용한 횟수, 뒤의 문자(0:A, 1:B, 2:C), 뒤의 뒤의 문자.
string s;
int A, B, C;
char ans[51];

bool go(int i, int a, int b, int p, int pp){
    if(i == s.size()) return true;//문제의 조건에 맞는 경우.
    
    if(dp[i][a][b][p][pp]) return false;//이미 이 상태에 도달한 경우.
    dp[i][a][b][p][pp]=true;
    
    if(a<A){
        ans[i]='A';
        if(go(i+1,a+1,b, 0, p)) return true;//바로 전 문자를 전전 문자로 보내고 전 문자를 0(A)로 한다.
    }
    
    if(b<B){
        if(p!=1){//바로 전 문자가 B이면 안됨.
            ans[i]='B';
            if(go(i+1,a,b+1, 1, p)) return true;
        }
    }
    
    if(i-a-b<C){
        if(p!=2 && pp != 2){//바로 전 문자와 전전 문자가 C이면 안됨.
            ans[i]='C';
            if(go(i+1,a,b, 2, p)) return true;
        }
    }
    
    return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> s;
    
    for(int i=0; i<s.size(); i++){
        if(s[i]=='A') A++;
        else if(s[i]=='B') B++;
        else C++;
    }
    
    if(go(0,0,0,0,0)) cout << ans;//A는 언제든 사용가능하므로 p와 pp에 0,0을 보냄.
    else cout << -1;
    
    return 0;
}
