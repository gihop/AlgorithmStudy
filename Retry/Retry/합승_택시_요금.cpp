#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <iostream>
#include <algorithm>

using namespace std;

/*
 solution은 다익스트라, solution2는 플로이드와샬로 풀었다.
 */

int INF = 987654321;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = INF;
    
    vector<vector<pair<int,int>>> graph(n+1);
    
    for(int i=0; i<fares.size(); i++){
        graph[fares[i][0]].push_back(make_pair(fares[i][2], fares[i][1]));
        graph[fares[i][1]].push_back(make_pair(fares[i][2], fares[i][0]));
    }
    
    vector<vector<int>> dp(n+1, vector<int>(n+1, INF));

    for(int i=1; i<=n; i++){
        if(i!=s && i!=a && i!=b) continue;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        dp[i][i] = 0;
        pq.push(make_pair(0, i));
        while(!pq.empty()){
            int cost, now;
            tie(cost, now) = pq.top();
            pq.pop();
            if(dp[i][now] < cost) continue;
            for(int j=0; j<graph[now].size(); j++){
                int next_cost, next;
                tie(next_cost, next) = graph[now][j];
                if(next_cost + cost < dp[i][next]){
                    dp[i][next] = next_cost + cost;
                    pq.push(make_pair(next_cost+cost, next));
                }
            }
        }
    }
    for(int i=1; i<=n; i++){
        if(dp[s][i]==INF || dp[a][i]==INF || dp[b][i]==INF) continue;
        answer = min(answer, dp[s][i]+dp[a][i]+dp[b][i]);
    }
    
    return answer;
}

int solution2(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = INF;
    
    vector<vector<int>> graph(n+1, vector<int>(n+1, INF));
    
    for(int i=0; i<fares.size(); i++){
        graph[fares[i][0]][fares[i][1]] = fares[i][2];
        graph[fares[i][1]][fares[i][0]] = fares[i][2];
    }
    
    for(int i=1; i<=n; i++){
        graph[i][i] = 0;
    }
    
    for(int t=1; t<=n; t++){
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                if(graph[i][j] > graph[i][t] + graph[t][j])
                    graph[i][j] = graph[i][t] + graph[t][j];
            }
        }
    }
    
    for(int i=1; i<=n; i++){
        if(graph[s][i] == INF || graph[a][i]==INF || graph[b][i]==INF) continue;
        answer = min(answer, graph[s][i]+graph[a][i]+graph[b][i]);
    }
    
    return answer;
}
