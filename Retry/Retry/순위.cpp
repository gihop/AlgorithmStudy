#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

/*
 이전에는 플로이드와샬로 풀었다.(직접 푼 것은 아니고 공부)
 이번에는 직접 풀었는데 그래프를 그렸을 때
 win[i][j]는 i가 이길 수 있는 선수의 번호를 저장하고,
 lost[i][j]는 i가 지는 선수의 번호를 저장한다.
 이렇게 했을 때 i가 무조건 이기는 선수의 수와 무조건 지는 선수의 수를 합쳐서
 이 수가 n-1이면 순서가 확정이 된다.
 이를 bfs로 풀었다.
 플로이드와샬과 속도 비교를 했을 때 비슷해서 써도 될 것 같다.
 */

int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    
    vector<vector<int>> win(n+1), lose(n+1);
    for(int i=0; i<results.size(); i++){
        win[results[i][0]].push_back(results[i][1]);
        lose[results[i][1]].push_back(results[i][0]);
    }
    
    for(int i=1; i<=n; i++){
        int count = 0;
        queue<int> q;
        q.emplace(i);
        vector<bool> visited(n+1, false);
        visited[i] = true;
        while(!q.empty()){
            int now = q.front();
            q.pop();
            for(int j=0; j<win[now].size(); j++){
                if(visited[win[now][j]]) continue;
                visited[win[now][j]] = true;
                count+=1;
                q.emplace(win[now][j]);
            }
        }
        q.emplace(i);
        visited.resize(n+1, false);
        while(!q.empty()){
            int now = q.front();
            q.pop();
            for(int j=0; j<lose[now].size(); j++){
                if(visited[lose[now][j]]) continue;
                visited[lose[now][j]] = true;
                count+=1;
                q.emplace(lose[now][j]);
            }
        }
        if(count == n-1) answer+=1;
    }

    return answer;
}

int solution2(int n, vector<vector<int>> results) {
    int answer = 0;
    
    vector<vector<bool>> graph(n+1, vector<bool>(n+1, false));
    
    for(int i=0; i<results.size(); i++)
        graph[results[i][0]][results[i][1]] = true;
    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            for(int k=1; k<=n; k++){
                if(graph[j][i] && graph[i][k]) graph[j][k] = true;
            }
        }
    }
    
    for(int i=1; i<=n; i++){
        int count = 0;
        for(int j=1; j<=n; j++){
            if(graph[i][j] || graph[j][i]) count++;
        }
        if(count == n-1) answer++;
    }
    
    return answer;
}
