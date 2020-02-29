//
//  이분_그래프_1707.cpp
//  DFS
//
//  Created by jiho park on 2020/02/29.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <vector>

#define endl "\n"
using namespace std;

//이 문제의 핵심은 무엇을 이분그래프로 볼것이냐이다.
//이분그래프 판단하는 방법을 몰라서 해맸었다. 블로그를 참고했다.
//이분그래프인지 결정하는 것은 정점을 흑과 백으로 나눌 때, 흑을 -1, 백을 1로 한다면
//백은 흑이랑만 연결되어야 하고, 흑은 백이랑만 연결되어야 한다.
//따라서 dfs 탐색을 할 때, 시작점을 백이라고 하면, 시작점과 연결되어 있는 정점은 흑으로 만들고, 그 다음 흑과 연결된 부분은 백으로 만든다.
//이 때 이미 색을 가지고 있는 정점을 만났을 때 색이 같다면 이분그래프가 아니다.
//첫 시작점인 1만 dfs를 해야하는게 아니라 1과 연결되지 않은 다른 이분그래프가 있으므로 주어진 V값에서 아직 방문하지 않은 정점들을 모두 dfs해야한다. 이 부분에서 틀렸습니다가 나왔었다.

int tc;
int check[20001];
int v,e;
vector<int> graph[20001];
bool ans;

void dfs(int n){
    int label = check[n];//현재 정점의 색깔(1은 백, -1은 흑으로 임의로 생각).
    for(int i=0; i<graph[n].size(); i++){
        int next = graph[n][i];
        if(!ans) return;//이미 이분 그래프가 아닌 경우 빠르게 dfs를 종료한다.
        if(check[next] == 0){//아직 방문하지 않은 정점인 경우.
            check[next] = label*-1;//흑(-1)이면 백(1), 백(1)이면, 흑(-1)로 저장.
            dfs(next);
        }
        else if(check[next] == label){//이미 방문한 정점인데 색깔이 같은 경우는 이분 그래프가 아니다.
            ans = false;
            return;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> tc;
    while(tc--){
        memset(check,0,sizeof(check));
        for(int i=1; i<20001; i++)//그래프를 매 테스트케이스 마다 초기화 해줘야 한다. 이 부분이 오래걸릴 것이라고 생각해서 다른 방법을 생각했으나 이게 맞다.
            graph[i].clear();
        cin >> v >> e;
        for(int i=0; i<e; i++){
            int a, b;
            cin >> a >> b;
            graph[a].push_back(b);//a와 b를 양방향으로 연결시켜준다.
            graph[b].push_back(a);
        }
        ans = true;
        for(int i=1; i<=v; i++){
            if(check[i]==0){//아직 방문하지 않은 정점인 경우.
                check[i]=1;//시작점을 1로 한다.
                dfs(i);
            }
        }
        
        if(ans) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    
    return 0;
}
