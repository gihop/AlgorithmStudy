//
//  ABC_12969.cpp
//  DP
//
//  Created by jiho park on 2020/03/06.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

#define endl "\n"
using namespace std;

//dfs+dp.
//풀이법을 떠올리기가 어렵다. 구조를 익히자.
//최종 문자열을 만드는데 dfs로 만든다.
//만들면서 0번째 원소부터 n-1번째 원소까지 순서대로 만드므로 A가 추가될 때는 A가 제일 작은 문자이므로 p가 추가되지 않는다.
//B가 추가되면 가지고 있던 A원소의 갯수만큼 p가 추가 된다.
//C가 추가되면 가지고 있던 A와 B의 원소의 갯수 만큼 p가 추가된다.

int n,k;
bool dp[31][31][31][436];//dp[i][a][b][p] i는 문자열 길이, a는 A의 갯수, b는 B의 갯수, p는 S[i]<S[j]를 만족하는 갯수.
char ans[31];

bool go(int i, int a, int b, int p){
    if(i==n){//길이가 입력의 n과 같아지면 문제의 조건 S[i]<S[j]를 만족하는 갯수 p가 입력받은 k와 같은지 검사한다.
        if(p==k) return true;
        else return false;
    }
    
    if(dp[i][a][b][p]) return false;//이미 검사한 부분인데 참이였다면 이미 이 재귀함수를 벗어났다. 그러므로 거짓.
    dp[i][a][b][p]=true;//방문 표시.
    
    ans[i]='A';//정답 문자열에서 i번째 원소가 A라고 한다면.
    if(go(i+1, a+1, b, p)) return true;//i==n일 때 까지 진행했을 때 참이였다면 바로 true를 반환해서 재귀함수를 빠르게 종료한다. 거짓이라면 B를 넣어본다. i번째 A를 넣는데 A보다 작은 원소는 없으므로 p는 늘어나지 않는다.
    
    ans[i]='B';
    if(go(i+1, a, b+1, p+a)) return true;//A의 원소의 갯수만큼 p가 추가된다.
    
    ans[i]='C';
    if(go(i+1, a, b, p+a+b)) return true;//C가 추가될 때는 A와 B의 원소의 갯수만큼 p가 추가된다.
    
    return false;//이 부분에 도달하면 입력 n,k에 만족하는 문자열이 없는 것. 즉 -1.
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> k;
    
    if(go(0,0,0,0)) cout << ans;
    else cout << -1;
    
    return 0;
}
