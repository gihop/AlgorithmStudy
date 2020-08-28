#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

//처음 풀어본 그래프 문제.

vector<vector<int>> graph;

int find(int start){
    bool visited[20000];
    memset(visited, false, sizeof(visited));
    
    queue<int> q;
    q.emplace(start);
    visited[start] = true;
    
    int answer = 0;
    
    while(true){
        int count = 0;
        int loop = q.size();
        //for문의 범위를 q.size()로 하면 안된다. q.emplace()로 q 사이즈가 계속 올라가기 때문이다.
        for(int i=0; i<loop; i++){
            int now = q.front();
            q.pop();
            for(int j=0; j<graph[now].size(); j++){
                if(!visited[graph[now][j]]){
                    visited[graph[now][j]] = true;
                    q.emplace(graph[now][j]);
                    count++;
                }
            }
        }
        if(q.empty())
            break;
        //answer = count가 q.empty() 탈출문보다 앞에 있으면 안된다.
        //맨 끝 노드로 탐색을 시작했을 때 count의 값은 0이라서 return이 무조건 0이기 때문이다.
        answer = count;
    }
    return answer;
}

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    
    graph.resize(n);
    
    for(int i=0; i<edge.size(); i++){
        graph[edge[i][0]-1].push_back(edge[i][1]-1);
        graph[edge[i][1]-1].push_back(edge[i][0]-1);
    }
    
    answer = find(0);
    
    return answer;
}
