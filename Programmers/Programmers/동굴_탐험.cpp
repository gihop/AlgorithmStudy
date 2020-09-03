#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <queue>
#include <map>

using namespace std;

//https://programmers.co.kr/learn/courses/30/lessons/67260#
//그래프 문제.
//효율성 1개 테스트케이스 시간초과, 정확성 1개 테스트케이스가 틀렸다. 합계 95.6점.
//처음에는 효율성도 맞추지 못했으나 block map을 추가해서
//navigate함수를 한번만 호출하도록 해서 효율성 테스트케이스 1개 빼고 해결했다.
//개선 사항이 떠오르지 않는다....
//개선 사항을 알아내면 다시 고쳐보겠다.

//추가+
//정확도 1개 틀린 이유를 찾았다.
//0번방을 가기 위해 들려야하는 조건이 있다면 탐색이 불가능하다.

vector<vector<int>> graph;
set<int> visited;//한 번이라도 방문했던 방을 저장한다.
map<int,int> orderMap;

void navigate(int start, int n){
    vector<bool> check(n, false);
    map<int,int> block;
    queue<int> q;
    q.emplace(0);
    check[0] = true;
    
    while(!q.empty()){
        int now = q.front();
        q.pop();
        for(int i=0; i<graph[now].size(); i++){
            int next = graph[now][i];
            if(check[next]) continue;//이미 방문했던 방은 가지 않는다.
            
            if(orderMap.count(next) > 0){//next방을 가기 전에 들려야하는 방이 있는 경우.
                if(visited.count(orderMap[next]) > 0){//next방을 가기 전에 들려야하는 방을 들린 경우.
                    q.emplace(next);
                    visited.insert(next);
                    check[next] = true;
                }
                else{//next방을 가기 전에 들려야하는 방을 들리지 않은 경우.
                    block[orderMap[next]] = now;//block map에 key로 가기전에 들려야하는 방과 value로 가지못한 현재 방을 저장한다.
                }
            }
            else{//아무 조건 없이 바로 갈 수 있는 방인 경우.
                if(visited.count(next) == 0){//처음 들리는 방인 경우.
                    visited.insert(next);
                    if(block.count(next) > 0){//처음 들리는 방이 이전에 들려야하는 방인데 들리지 않았던 방인 경우.
                        q.emplace(block[next]);//큐에 추가해서 막혔던 방을 바로 갈 수 있도록 한다.
                    }
                }
                q.emplace(next);
                check[next] = true;
            }
        }
    }
}

bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
    bool answer = true;
    
    graph.resize(n);
    
    //key방으로 가기 위해 먼저 가야하는 value방을 저장한다.
    for(int i=0; i<order.size(); i++){
        orderMap[order[i][1]] = order[i][0];
        if(order[i][1] == 0) return false;//0번방이 출발지점이기 때문에 0으로 가기 전에 가야할 방이 있다면 탐색이 불가능하다.
    }
    
    //그래프 문제의 필수 자료구조.
    for(int i=0; i<path.size(); i++){
        graph[path[i][0]].push_back(path[i][1]);
        graph[path[i][1]].push_back(path[i][0]);
    }
    
    visited.insert(0);
    
    navigate(0, n);
    
    if(n == visited.size()) answer = true;
    else answer = false;
    
    return answer;
}
