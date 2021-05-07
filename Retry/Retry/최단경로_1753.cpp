#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

/*
 다익스트라 문제.
 내가 했던 실수는 pq에 넣을 때 weight, vertex를 넣어야하는데
 vertex, weight를 넣어서 heap이 제대로 동작하지 않았기 때문이다.
 */

int INF = 987654321;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int V, E;
    cin >> V >> E;
    
    vector<vector<pair<int,int>>> vertex(V+1);
    
    int start;
    cin >> start;
    
    for(int i=0; i<E; i++){
        int u, v, w;
        cin >> u >> v >> w;
        vertex[u].push_back(make_pair(v, w));
    }
    
    vector<int> paths(V+1, INF);
    paths[start] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    
    pq.push(make_pair(0, start));
    while(!pq.empty()){
        int now, weight;
        tie(weight, now) = pq.top();
        pq.pop();
        if(weight > paths[now]) continue;
        for(int i=0; i<vertex[now].size(); i++){
            int next, next_weight;
            tie(next, next_weight) = vertex[now][i];
            if(weight + next_weight < paths[next]){
                paths[next] = weight + next_weight;
                pq.push(make_pair(weight+next_weight, next));
            }
        }
    }
    for(int i=1; i<=V; i++){
        if(paths[i] == INF) cout << "INF" << '\n';
        else cout << paths[i] << "\n";
    }
    
    return 0;
}
