//
//  N-Rook_II_1767.cpp
//  DP
//
//  Created by jiho park on 2020/03/08.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>

#define endl "\n"
using namespace std;

//굉장히 어려운 문제. 절대 스스로 못 풀 듯..

int N,M,K;
int INF=1000001;
long long dp[101][101][101];//dp[n][m][k]는 n행이 남았고 m개의 열에만 놓을 수 있고 앞으로 k개의 룩을 더 놓아야 한다는 뜻이다.

long long go(int n, int m, int k){
    if(n<0 || m<0 || k<0) return 0;
    if(k==0) return 1;
    
    if(dp[n][m][k]!=-1) return dp[n][m][k];
    
    //맵을 만드는 경우의 수는
    //행에 룩이 속한 행과 열에 다른 룩이 없는 경우.
    //행에 룩이 두개이고 각 두개의 룩의 열에는 다른 룩이 없는 경우.
    //열에 룩이 두개이고 각 두개의 룩의 행에는 다른 룩이 없는 경우이다.
    long long num=0;
    //자 머리속에서 그림을 그려보자.
    //nxm의 지도를 그려놓고, 놓을 수 있는 행과 열을 지워나간다고 생각하자.
    num += go(n-1,m,k)%INF;//이 경우는 행에서 룩을 놓지 않는 경우이다. 현재 행을 삭제하고 다음 행으로 넘어가고 룩을 놓지 않았으므로 m개의 열 그대로 살아있고, k개의 룩을 더 놓아야 한다.
    num += go(n-1,m-1,k-1)*m%INF;//한 개의 룩을 행에 놓으면서 어떤 룩에게도(앞으로도) 공격을 받지 않는 경우. 앞으로도 공격을 받지 않을 것이기 때문에 룩을 놓는 열에는 다른 룩을 놓을 수 없게 m의 갯수를 한 개 줄인다. 놓아야 할 룩의 갯수도 k-1 줄어든다. 또한 m개의 열 중에 아무곳이나 놓을 수 있으므로 경우의 수가 m개 곱해져야한다.
    num += go(n-1,m-2,k-2)*m*(m-1)/2%INF;//두 개의 룩을 행에 놓는 경우. 이미 서로 한 번씩 공격을 받기 때문에 더 이상 공격을 받으면 안된다. 그래서 각각 놓여진 두 개의 열을 다음 놓을 차례에서 삭제해야하므로 m-2이다. k도 당연히 2개 줄어들고 이 행에서 두 개의 룩 m개의 칸에 놓을 수 있는 경우의 수는 m*(m-1)/2 = mC2 (C=Combination, 고등학교때 배운거)이므로 경우의 수에 m*(m-1)/2 곱해줘야한다.
    num += go(n-2,m-1,k-2)*m*(n-1)%INF;//(이해가 잘 안 갔던 부분) 두 개의 룩을 열에 놓는 경우. 남아있는 m개의 열에는 어차피 다른 룩이 없다. 그래서 m개의 열중에 하나를 고른다. 두 개의 룩을 놓는데 한 개는 현재 n행에 놓고 나머지 한 개는 현재 n행을 제외한 놓을 수 있는 n-1개의 행에 놓을 수 있다. 현재 행을 포함해서 다른 행에도 룩을 놓았으니 그 행 까지 삭제해야 하므로 n-2. 하나의 열을 골라서 놓았고 앞으로 공격 받으면 안되므로 해당 열 삭제 m-1, 두 개의 룩을 놓았으므로 k-2. 앞에 설명했듯 m개의 열중에 하나 골라서 현재 행에 룩을 하나 놓고 n-1개의 행에 룩을 하나 더 놓을 수 있으므로 경우의 수는 m*(n-1)이다.
    dp[n][m][k] = num%INF;
    
    return dp[n][m][k];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    memset(dp, -1, sizeof(dp));
    
    cin >> N >> M >> K;
    
    cout << go(N,M,K);
    
    return 0;
}
