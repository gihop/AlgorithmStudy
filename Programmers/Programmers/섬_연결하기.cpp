#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

//각 정점에 연결된 간선들이 있을 때(이 때 갈 수 없는 정점은 없다)
//간선의 비용을 최소로 해서 모든 정점을 연결 시키는 것.
//그것은 최소 신장 트리를 구하는 것이다.

//처음에 이 문제를 풀 때 주어진 간선들로 조합을 만들어서 bfs로 모두 연결되는지 확인을 했다.
//이렇게 풀었을 때는 시간초과가 발생했다.
//이전에 풀은 코드는 밑에 주석처리 되어 있다.

//간선들로 조합을 만들 필요 없다.
//우선 간선들을 비용을 기준으로 오름차순으로 정렬한다.
//그 다음 최소 비용부터 순서대로 최소신장트리(정답인 트리)에 포함을 시키고
//이 때 간선의 두 정점이 이미 트리에 포함이 되어있다면 그 간선은 제외시킨다.
//두 정점이 이미 포함되어 있다면 cycle이 만들어진다.
//예를 들어 1 <-> 2, 1 <-> 3 간선이 최소신장트리에 포함되어 있을 때,
//2 <-> 3을 포함시키면 2,3은 이미 포함된 정점이라서 cycle이 만들어진다.

//이를 구현하기 위해서 cycle table을 만든다.
//cycle table은 최초로 각 정점에 해당하는 숫자를 원소의 숫자로 갖는다.
//n=5이면 각 원소로 0, 1, 2, 3, 4를 갖는다.
//cycle[n] = m 이 의미는 n번째 정점의 부모는 m이라는 뜻이다.
//그 다음, 간선 0 <-> 1이 최소 비용 1을 가질 때,
//정점 0의 부모는 0 자신이고, 정점 1의 부모는 1 자신이다.
//이 때 서로 부모가 다르므로, 1의 부모를 정점 0으로 한다. (일반적으로 작은 숫자 정점을 부모로 한다.)
//이런 방식으로 간선을 추가하고, 서로 부모가 같은 경우(포함 시켰을 때 cycle 발생)는 포함시키지 않는다.

/* 이것이 *****%%%%""""크루스칼 알고리즘""""%%%%***** 이다.*/

vector<int> cycle;

bool compare(const vector<int> &a, const vector<int> &b){
    if(a[2]<b[2]) return true;
    else return false;
}

int findParent(int child){
    if(cycle[child] == child) return child;
    else return findParent(cycle[child]);
}

pair<int,int> find(int a, int b){
    int parentA = findParent(a);
    int parentB = findParent(b);
    
    return make_pair(parentA, parentB);
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    
    sort(costs.begin(), costs.end(), compare);
    
    for(int i=0; i<n; i++)
        cycle.push_back(i);
    
    for(int i=0; i<costs.size(); i++){
        int a = costs[i][0], b = costs[i][1];
        
        int parentA, parentB;
        tie(parentA, parentB) = find(a,b);
        
        if(parentA != parentB){//이 부분이 크루스칼 알고리즘의 핵심.
            if(parentA < parentB) cycle[parentB] = cycle[parentA];//find로 찾은 parentA를 cycle에 넣어서 변경해야한다. find로 child를 넣으면 모두 부모로 찾아가기 때문에 child인 a를 변경시키면 의미가 없다. cycle[b] = cycle[a]로 해서 틀렸었다.
            else cycle[parentA] = cycle[parentB];
            answer += costs[i][2];
        }
    }
    
    return answer;
}

//#include <string>
//#include <vector>
//#include <map>
//#include <tuple>
//#include <queue>
//#include <set>
//#include <iostream>
//#include <algorithm>
//
//using namespace std;
//
//vector<vector<int>> g;
//vector<vector<int>> graph;
//map<pair<int,int>,bool> m;
//int N, answer = 987654321;
//
//bool checkConnection(){
//    vector<bool> visited(N, false);
//    int start = 0;
//    visited[start] = true;
//    int count = 1;
//
//    queue<int> q;
//    q.emplace(start);
//    while(!q.empty()){
//        int now = q.front();
//        q.pop();
//        for(int i=0; i<g[now].size(); i++){
//            int next = g[now][i];
//
//            if(visited[next] == false && m.count(make_pair(now,next))>0 && m[make_pair(now,next)] == true){
//                visited[next] = true;
//                q.emplace(next);
//                count++;
//            }
//            else if(visited[next] == false && m.count(make_pair(next,now))>0 && m[make_pair(next,now)] == true){
//                visited[next] = true;
//                q.emplace(next);
//                count++;
//            }
//        }
//    }
//    if(count == N) return true;
//    else return false;
//}
//
//void go(map<pair<int,int>,bool>::iterator start, int count, int cost){
//    if(count > 0 && cost < answer){
//        if(checkConnection()){
//            answer = cost;
//            return;
//        }
//    }
//    for(map<pair<int,int>,bool>::iterator iter = start; iter != m.end(); iter++){
//        if(iter->second) continue;
//        if(cost+graph[(iter->first).first][(iter->first).second] >= answer) continue;
//        iter->second = true;
//        go(iter, count+1, cost+graph[(iter->first).first][(iter->first).second]);
//        iter->second = false;
//    }
//}
//
//
//int solution(int n, vector<vector<int>> costs) {
//    N = n;
//
//    graph.resize(n, vector<int>(n, 0));
//    g.resize(n);
//
//    for(int i=0; i<costs.size(); i++){
//        g[costs[i][0]].push_back(costs[i][1]);
//        g[costs[i][1]].push_back(costs[i][0]);
//        graph[costs[i][0]][costs[i][1]] = costs[i][2];
//        graph[costs[i][1]][costs[i][0]] = costs[i][2];
//        m[make_pair(costs[i][0], costs[i][1])] = false;
//    }
//
//    go(m.begin(), 0, 0);
//
//    return answer;
//}
