#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/*
 cost가 큰 순서로 정렬을 한 뒤에 해당 간선을 뺏을 때
 모든 정점이 연결되는 경우 해당 간선의 cost를 전체 cost에서 빼주는 방식으로 해결했다.
 추가로 실수를 해서 디버깅하는데 오래 걸렸었다.(밑에 주석 있음).
 */

vector<bool> visited;

bool compare(vector<int> const &a, vector<int> const &b){
    if(a[2] > b[2]) return true;
    else return false;
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    
    sort(costs.begin(), costs.end(), compare);
    
    vector<vector<pair<int,int>>> graph(n);
    
    for(int i=0; i<costs.size(); i++){
        graph[costs[i][0]].push_back(make_pair(costs[i][1],costs[i][2]));
        graph[costs[i][1]].push_back(make_pair(costs[i][0],costs[i][2]));
        answer += costs[i][2];
    }
    
    for(int i=0; i<costs.size(); i++){
        tuple<int,int,int> ban = make_tuple(max(costs[i][0], costs[i][1]), min(costs[i][0], costs[i][1]), costs[i][2]);
        vector<bool> visited(n, false);
        queue<int> q;
        visited[0] = true;
        q.emplace(0);
        int count = 1;
        while(!q.empty()){
            int now = q.front();
            q.pop();
            for(int j=0; j<graph[now].size(); j++){
                if(make_tuple(max(now, graph[now][j].first), min(now, graph[now][j].first), graph[now][j].second) == ban) continue;
                if(visited[graph[now][j].first]) continue;
                visited[graph[now][j].first] = true;
                q.emplace(graph[now][j].first);
                count+=1;
            }
        }
        if(count == n){
            for(int j=0; j<graph[costs[i][0]].size(); j++){ // j++를 i++라고 함...
                if(make_pair(costs[i][1], costs[i][2]) == graph[costs[i][0]][j]){
                    graph[costs[i][0]].erase(graph[costs[i][0]].begin() + j);
                    break;
                }
            }
            for(int j=0; j<graph[costs[i][1]].size(); j++){
                if(make_pair(costs[i][0], costs[i][2]) == graph[costs[i][1]][j]){
                    graph[costs[i][1]].erase(graph[costs[i][1]].begin() + j);
                    break;
                }
            }
            answer -= costs[i][2];
        }
    }
    
    return answer;
}
