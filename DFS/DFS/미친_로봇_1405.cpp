//
//  미친_로봇_1405.cpp
//  DFS
//
//  Created by jiho park on 2020/03/02.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>

#define endl "\n"
using namespace std;

//무난한 백트래킹 문제이나 cout.precision을 안해줘서 틀렸었다.
//cout.precision은 굳이 몰라도 될 것 같다.
//처음에 로봇이 dfs로 n만큼 움직였을 때 check배열에 1보다 큰 숫자가 있다면(중복 방문) 이동 경로가 단순하지 않다를 의미함으로 확률을 더하지 않는 방식으로 풀었었는데 시간초과가 났다.
//그래서 이미 방문한 곳은 아예 방문하지 않고 n번 이동했을 때의 확률을 더하면 check배열에 1보다 큰 숫자가 있는지 확인할 필요도 없고 필요한 이동경로만 가기 때문에 시간초과를 없앨 수 있었다.
//문제의 조건에 의하면 확률이 0인 방향도 있을 수 있다. 그래서 이 부분도 처리를 해줘야 한다. 문제를 잘 읽어야 한다.

int a[29][29];
int check[29][29];
int n;
int probs[4];
int dx[]={0, 0, 1, -1};
int dy[]={1, -1, 0, 0};
double ans;

void dfs(int x, int y, int cnt, double prob){
    if(cnt==n){
        ans+=prob;//전체 확률에 더한다.
        return;
    }
    for(int i=0; i<4; i++){
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(check[nx][ny]>0 || probs[i]==0) continue;//이미 방문한 곳이거나 현재 방향으로 이동할 확률이 0이라면 가지 않는다.
        check[nx][ny]+=1;
        prob = prob*(probs[i]/100.0);//현재 방향에 대한 확률을 곱해준다.
        dfs(nx, ny, cnt+1, prob);
        prob = prob*(100.0/probs[i]);//백트래킹. 확률을 역수로 곱해준다.
        check[nx][ny]-=1;//백트래킹.
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> probs[0] >> probs[1] >> probs[2] >> probs[3];
    
    check[14][14]=1;
    dfs(14,14,0,1);//(14,14)가 중앙이라서 이 곳에서 로봇이 이동을 시작해야한다.
    
    cout.precision(11);
    cout << ans;
    
    return 0;
}
