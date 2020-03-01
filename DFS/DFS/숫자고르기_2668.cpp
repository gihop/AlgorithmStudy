//
//  숫자고르기_2668.cpp
//  DFS
//
//  Created by jiho park on 2020/03/01.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>

#define endl "\n"
using namespace std;

//짜증으로 화병이 걸릴 뻔한 문제.
//처음에 조합 뽑기로 생각해서 dfs를 만들었는데 그렇게 했을 경우
//1
//1 2
//1 2 3
//1 2 3 4
//1 2 3 4 5
//1 2 3 5
//1 2 4
//1 2 4 5
//이런 방식으로 dfs를 모두 돌리는데 이렇게 했을 경우 시간초과가 발생한다.
//이렇게 하면 안되고 문제의 테스트 케이스를 보면
//1 2 3 4 5 6 7
//3 1 1 5 5 4 6
//여기서 1->3, 3->1 =>사이클이 발생하므로 이 숫자들을 벡터에 넣어준다.
//5->5 역시 사이클 발생으로 벡터에 넣어준다.
//2->1, 1->3, 3->1 에서는 처음 숫자와는 다른데 이미 방문했던 숫자 1이 나오므로 사이클이 아니다.
//2->1에서 1은 이미 사이클에 성공했으므로 이 부분에서 그만둘수록 더 최적화를 할 수도 있다.
//이 부분은 텀_프로젝트_9466에서 볼 수 있다.
//dfs를 더 연습해야할 것 같다.

int a[101];
bool visited[101];
bool cycle[101];
int n;
vector<int> v;

void dfs(int num, int start){
    int next = a[num];
    if(next == start){
        visited[start]=true;
        for(int i=1; i<=n; i++){
            if(!visited[i]) continue;
            cycle[i]=true;
            v.push_back(i);
        }
        visited[start]=false;
        return;
    }
    if(visited[next]) return;
    visited[next]=true;
    dfs(next, start);
    visited[next]=false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n;
    
    for(int i=1; i<=n; i++)
        cin >> a[i];
    
    for(int i=1; i<=n; i++){
        if(cycle[i]) continue;
        dfs(i,i);
    }
    
    cout << v.size() << endl;
    sort(v.begin(), v.end());
    for(int i=0; i<v.size(); i++)
        cout << v[i] << endl;
    
    return 0;
}
