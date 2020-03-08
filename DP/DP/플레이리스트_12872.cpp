//
//  플레이리스트_12872.cpp
//  DP
//
//  Created by jiho park on 2020/03/08.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>

#define endl "\n"
using namespace std;

//dp는 내 뇌랑 잘 안맞는 것 같다.
//이 문제는 꼭 다시 풀어보자. 다른 코드 보고 이해하는데도 한 세월 걸린 문제.
//처음에 접근할 때 몇번째 플레이리스트에 뭘 들었는지를 저장하려고 생각했고 이에 대한 dp배열을 생각을 하지 못했다.
//이렇게 할 필요 없이 이미 들은 노래 종류 갯수, 아직 듣지 않은 노래 종류 갯수로 나누면 된다.
//뭘 들었는지 알아야된다고 생각했는데 알 필요가 없다.

long long dp[101][101];//원래는 dp[p][x][y] 구조임. p번째 노래 선택에 이미 들은 노래 종류의 갯수가 x개, 아직 듣지 않은 노래 종류의 갯수가 y개를 의미한다. 여기서 y는 N-x개이므로 생략가능하다.
int N,M,P;//N은 총 노래의 갯수, M은 같은 노래를 들으려 할 때 같은 노래 사이에 종류가 다른 M개의 노래가 있어야 함을 뜻함. 총 P개를 플레이리스트에 넣을 것.
int INF=1000000007;

long long go(int p, int x, int y){
    if(p == P){
        if(y==0) return 1;
        else return 0;
    }
    if(dp[p][x]!=-1) return dp[p][x];
    long long ans=0;
    if(y>0) ans += go(p+1, x+1, y-1)*y%INF;//이게 무슨 소린지 이해하는지 정말 오래 걸림. 아직 듣지 않은 노래가 있을 때, 플레이리스트에 추가할 수 있는 노래는 아직 듣지 않은 노래 갯수 y개 전체 아무거나 들을 수 있기 때문에 결과값에 y개를 곱해준다.
    if(x>M) ans += go(p+1, x, y)*(x-M)%INF;//이 것 또한 무슨 소린지 이해하는데 정말 오래 걸림. 이미 들은 노래를 들으려고 할 때, M개 앞에 노래는 모두 다른 종류의 노래여야 한다. 즉 M개의 다른 종류 노래가 필요하고 M개의 종류는 다시 들을 수 없다. 따라서 이미 들은 노래를 들으려면 최소 M+1개의 노래 종류를 이미 들어야 하기 때문에 x>M이다. 다시 들을 수 있는 노래의 갯수는 현재 이미 들은 노래 갯수 x에서 M을 뺀 수이기 때문에 x-M을 곱해줘야한다.
    dp[p][x] = ans%INF;
    
    return dp[p][x];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    memset(dp, -1, sizeof(dp));
    
    cin >> N >> M >> P;
    
    cout << go(0,0,N);
    
    return 0;
}
