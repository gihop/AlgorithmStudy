#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <iostream>

using namespace std;

// 정말 어려웠던 최소 비용 문제.(최소 비용 문제에 약하다.)
// 처음에는 bfs로 풀었다. bfs 코드는 solution2. (bfs를 최대한 최적화 해도 효율성에서 2개의 케이스에서 시간초과가 발생해서 95점이 나왔다.)
// ++bfs로도 풀었다.
// 이를 해결하기 위해서 다익스트라 알고리즘을 사용했다.
// 이 문제를 python에서 다익스트라를 사용했던 방법 그대로 사용했을 때 시간초과가 발생했다.
// 이를 해결하기 위해서 시도해본 방법들을 소개한다.

/*
 bfs로 풀었던 방법.
 bfs로 이 문제를 풀지 못하는 줄 알았는데 graph를 밑의 1번 방법을 사용하니 시간초과가 발생하지 않았다.
 쉽게 설명하면 경유하는(a와 b가 같이 갈) 정점을 찾는 것이 문제이기 때문에
 시작 정점에서 bfs로 각 정점의 최소 거리를 구한다. 이를 distance에 저장한다.
 그 다음 모든 정점에서 distance를 더한 값에 각 a와 b로 최소 거리를 구하는 방식을 사용했다.
 즉 bfs를 두번 사용하는 간단한 방법이다.
 중간 중간 최적화를 위한 부분이 있으니 solution2의 주석을 참고하자.
 */

/*
 1. 처음에는 graph에 전체 정점 수 만큼 0으로 초기화를 시켜놓고 간선이 있는 부분만 업데이트 해놓고
 다익스트라 내에서 0인 부분을 제외하고 탐색하는 방식을 사용했다.
 이 때 매번 n번 iteration이 발생하기 때문에 시간초과를 줄이기 위해서
 graph에 간선만 담을 수 있도록 구조를 바꿨다.
 하지만 이것으로 시간초과를 해결할 수는 없었다.
 */

/*
 2. 문제에 예시 2번과 3번을 보면 시작 정점에서 닿을 수 없는 정점들이 존재하는데
 이 부분도 다익스트라로 불필요한 탐색을 하기 때문에 처음에 시작 정점에서 닿을 수 있는 정점들만 bfs 탐색으로
 정리해서 닿을 수 있는 정점만 다익스트라를 사용하도록 수정했다.
 하지만 이도 시간 초과를 해결하지는 못했다.
 */

/*
 3. 해결 방법은 의외로 간단했다.
 이 문제를 푸는 핵심 아이디어는 각 정점에서 다른 정점간의 최소 비용을 다익스트라를 통해 정리를 한 뒤에
 시작 정점과, a가 도착해야 하는 정점, b가 도착 해야하는 정점은 모두 정해져 있고 같이 경유할 정점만 정하면 되기 때문에
 iteration을 돌면서 경유할 정점을 찾으면 된다.
 python에서는 모든 정점을 시작 노드로 설정하고 나머지 정점에 대한 최소 비용을 다익스트라로 정리해도 시간초과가 나지 않았다.
 하지만 여기서 간선에 방향이 없기 때문에 굳이 모든 정점에서 출발할 필요가 없었다.
 여기서 다익스트라를 한 번 돌리면 처음 출발하는 정점s에서 나머지 정점으로 가는 최소 비용 배열 dp[s][n]이 구해진다.
 즉 시작 정점 s, a, b가 있고 경유할 정점이 i일 때,
 결국 찾아야 하는 것은 dp[s][i] + dp[a][i] + dp[b][i]의 최소를 찾으면 되기 때문에
 모든 정점에서 다익스트라를 구할 필요 없이 s, a, b 정점에서만 다익스트라를 사용하면 됐던 것이다.(python에서는 모든 정점을 해도 돌아갔다.)
 */

/*
 문제의 특성에 따라, 언어에 따라 다익스트라가 플로이드 와샬보다 느려질 수 있다고 한다.
 이 문제도 python에서는 모든 정점을 다익스트라 해도 문제 없었는데 c++ 에서는 한번 더 최적화가 필요했던 것이다.
 c++에서는 플로이드 와샬이 좀 더 최적화가 잘된 문제인 것 같다.
 */

int INF = 987654321;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = 987654321;
    
    vector<vector<pair<int,int>>> graph(n+1);
    
    for(int i=0; i<fares.size(); i++){
        graph[fares[i][0]].push_back(make_pair(fares[i][1], fares[i][2]));
        graph[fares[i][1]].push_back(make_pair(fares[i][0], fares[i][2]));
    }
    
    vector<vector<int>> dp(n+1, vector<int>(n+1, INF));
    
    for(int i=1; i<n+1; i++){
        if(i != a && i != b && i != s) continue;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.emplace(i, 0);
        dp[i][i] = 0;
        while(!pq.empty()){
            int now, fare;
            tie(now, fare) = pq.top();
            pq.pop();
            if(dp[i][now] < fare) continue; // pq내에 최소 거리가 아니어서 뒤로 밀린 경우에는 iteration을 돌 필요가 없다.
            for(int j=0; j<graph[now].size(); j++){
                int next, next_fare;
                tie(next, next_fare) = graph[now][j];
                if(next_fare + fare < dp[i][next]){
                    dp[i][next] = next_fare + fare;
                    pq.emplace(next, next_fare + fare);
                }
            }
        }
    }
    
    for(int i=1; i<n+1; i++){
        if(dp[s][i] == INF || dp[a][i] == INF || dp[b][i] == INF) continue;
        answer = min(answer, dp[s][i] + dp[a][i] + dp[b][i]);
    }
    return answer;
}

int solution2(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = 987654321;
    
    vector<vector<pair<int,int>>> graph(n+1);
    
    for(int i=0; i<fares.size(); i++){
        graph[fares[i][0]].push_back(make_pair(fares[i][1], fares[i][2]));
        graph[fares[i][1]].push_back(make_pair(fares[i][0], fares[i][2]));
    }
    
    vector<int> distance(n+1, -1); // 시작 정점에서 나머지 정점의 최소 거리를 저장할 배열.
    
    queue<pair<int,int>> q;
    q.emplace(s, 0);
    distance[s] = 0;
    
    while(!q.empty()){
        int now, fare;
        tie(now, fare) = q.front();
        q.pop();
        for(int i=0; i<graph[now].size(); i++){
            int next, next_fare;
            tie(next, next_fare) = graph[now][i];
            if(distance[next] != -1 && distance[next] <= fare + next_fare) continue; // 이미 다녀간 정점인데 거리를 줄일 수 없는 경우.
            distance[next] = fare + next_fare;
            q.emplace(next, fare + next_fare);
        }
    }
    
    for(int i=1; i<n+1; i++){ // 경유할 정점 i에서 a,b의 도착지점을 찾는다.
        if(distance[i] == -1) continue; // 시작 정점에서 도달할 수 없는 정점인 경우.
        if(distance[i] > answer) continue; // 이미 경유 지점에서 최소 거리를 초과한 경우.
        q.emplace(i, 0);
        vector<int> dp(n+1, -1); // 경유 지점에서 나머지 정점사이의 최소 거리를 저장.
        dp[i] = 0;
        while(!q.empty()){
            int now, fare;
            tie(now, fare) = q.front();
            q.pop();
            if(fare + distance[i] > answer) continue;
            for(int i=0; i<graph[now].size(); i++){
                int next, next_fare;
                tie(next, next_fare) = graph[now][i];
                if(dp[next] != -1 && dp[next] <= fare + next_fare) continue;
                dp[next] = fare + next_fare;
                q.emplace(next, fare + next_fare);
            }
        }
        if(dp[a] != -1 && dp[b] != -1 && dp[a] + dp[b] + distance[i] < answer) // a와 b의 도착 지점에 도달 가능해야하고 그 거리의 합이 최소인 경우.
            answer = dp[a] + dp[b] + distance[i];
    }
    
    return answer;
}

int main(){
    vector<vector<int>> fares = {{5, 7, 9}, {4, 6, 4}, {3, 6, 1}, {3, 2, 3}, {2, 1, 6}};
    solution(7,3,4,1, fares);
    
    return 0;
}
//{{4, 1, 10}, {3, 5, 24}, {5, 6, 2}, {3, 1, 41}, {5, 1, 24}, {4, 6, 50}, {2, 4, 66}, {2, 3, 22}, {1, 6, 25}};
