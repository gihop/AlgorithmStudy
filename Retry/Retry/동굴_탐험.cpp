#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <set>
#include <queue>
#include <iostream>

using namespace std;

/*
 처음에 풀었던 방법은 [A,B] A를 가야만 B를 갈 수 있을 때
 A를 가지않고 B를 가게되면 아예 갈 수 없고
 A를 가면 B로 바로 이동할 수 있도록 했다.
 하지만
        0
      /   \
     1     2
     |    / \
     3   4   5
         |
         6
 이렇게 되어있을 때 order가 [[4,2],[3,6]]이면
 4로 도달할 수 없음에도 3으로 가면 6으로 가고 4로 도달이 가능하다.
 그래서 바꾼 것은 [A,B]일 때 A에 방문하지 않고 B를 갔을 때
 원래는 방문을 체크하지 않았지만 방문을 체크한다.
 그 뒤로 A에 도달하게 됐을 때 B가 방문이 true라면 바로 B를 queue에 넣어준다.
 이 때 B를 방문하지 않았을 경우 먼저 들려야할 장소가 필요한 노드를 저장하는 set에서 제거해주고
 나중에 B를 방문할 때 바로 방문할 수 있도록 바꿔주었다.
 */

bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
    vector<vector<int>> graph(n);
    map<int,int> order_map;
    vector<bool> visited(n, false);
    set<int> ban;
    
    for(int i=0; i<order.size(); i++){
        if(order[i][1] == 0) return false;
        order_map[order[i][0]] = order[i][1];
        ban.insert(order[i][1]);
    }
    
    for(int i=0; i<path.size(); i++){
        graph[path[i][0]].push_back(path[i][1]);
        graph[path[i][1]].push_back(path[i][0]);
    }
    queue<int> q;
    visited[0] = true;
    q.emplace(0);
    int count = 1;
    while(!q.empty()){
        int now = q.front();
        q.pop();
        if(order_map.count(now) > 0){
            if(visited[order_map[now]]){
                q.emplace(order_map[now]);
                count++;
            }
            ban.erase(order_map[now]);
        }
        for(int i=0; i<graph[now].size(); i++){
            int next = graph[now][i];
            if(visited[next]) continue;
            visited[next] = true;
            if(ban.count(next) > 0) continue;
            q.emplace(next);
            count++;
        }
    }
   
    if(count == n) return true;
    else return false;
}
