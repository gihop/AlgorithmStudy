#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <iostream>

using namespace std;

bool visited[20001];
int max_depth;
vector<vector<int>> graph;

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    
    graph.resize(n+1);
    for(int i=0; i<edge.size(); i++){
        graph[edge[i][0]].push_back(edge[i][1]);
        graph[edge[i][1]].push_back(edge[i][0]);
    }
    
    queue<pair<int,int>> q;
    visited[1] = true;
    q.emplace(1, 0);
    
    while(!q.empty()){
        int now, depth;
        tie(now, depth) = q.front();
        q.pop();
        if(depth > max_depth){
            max_depth = depth;
            answer = 1;
        }
        else if(depth == max_depth) answer+=1;
        
        for(int i=0; i<graph[now].size(); i++){
            if(visited[graph[now][i]]) continue;
            visited[graph[now][i]] = true;
            q.emplace(graph[now][i], depth+1);
        }
    }
    
    return answer;
}
