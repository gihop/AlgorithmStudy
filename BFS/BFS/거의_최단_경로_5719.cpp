//
//  거의_최단_경로_5719.cpp
//  BFS
//
//  Created by jiho park on 2020/02/16.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <tuple>
#include <cstring>
#include <vector>
#include <map>

#define endl "\n"
using namespace std;

//다익스트라를 써야 시간초과가 안나는 듯 하다.
//다익스트라 개념과 구현방법을 잘 익혀두자.
//꼭 다시 풀어보자.

int INF = 999999999;//그래프 정점의 초기값.
int n,m;
vector<pair<int,int>> graph[500];//처음에 입력하는 그래프 정보를 저장한다.
vector<int> trace[500];//최단경로를 저장하기 위한 벡터. nVertex가 어디서와야 최단 경로인지를 저장함.

vector<int> dijkstra(int Start){//다익스트라 알고리즘.
    vector<int> distance(n, INF);//시작점으로부터 각 정점으로 가기위한 최단 거리를 뜻함. n개의 정점을 거리값을 INF로 초기화 해줌.
    distance[Start] = 0;//시작점으로 가기위한 최단 거리는 0.
    
    priority_queue<pair<int,int>> pq;//cost, vertex; cost부터 해야 priority가 의미가 있음. default는 내림차순임. 거리가 작은 것 부터 뽑기 위해서 pq에 push 할 때 음수로 푸시함. priority_queue의 top은 맨 앞 원소를 말함. 그래서 오름차순으로 뽑기 위해서 음수.
    pq.push(make_pair(0,Start));
    
    while(!pq.empty()){
        int cost, vertex;
        tie(cost, vertex) = pq.top();
        cost*=-1;//음수로 저장된 cost를 다시 양수로 바꿔줌.
        pq.pop();
        
        if(distance[vertex] < cost) continue;//이미 더 짧은 거리로 pq를 통해서 갱신된 정점으로 더 거리가 긴 경로로 도착했을 경우.
        
        for(int i=0; i<graph[vertex].size(); i++){//해당 정점에서 갈 수 있는 모든 정점을 검사함.
            int nVertex, nCost;//갈 수 있는 정점과 cost.
            tie(nVertex, nCost) = graph[vertex][i];
            
            if(nCost == -1) continue;//bfs에서 제거된 간선인 경우.
            
            nCost += cost;//이전 정점의 cost와 더함.
            
            if(distance[nVertex] > nCost){//정점에 저장된 cost보다 시작점에서 부터의 거리가 더 짧은 경우 정점의 cost를 갱신해줘야 함.
                distance[nVertex] = nCost;
                pq.push(make_pair(-nCost, nVertex));//pq에는 음수로 저장함.
                
                trace[nVertex].clear();
                trace[nVertex].push_back(vertex);//nVertex는 vertex에서 왔을 때 최단 경로.
            }
            else if(distance[nVertex] == nCost){//정점에 저장된 cost와 시작점에서 부터의 거리가 같다면 nVertex로 가기 위한 최단경로가 또 있다는 뜻임. 그래서 더 추가해줌.
                trace[nVertex].push_back(vertex);
            }
        }
    }
    return distance;//최종 거의 최단 거리를 구하기 위해 반환.
}

void bfs(int End){//최단 경로를 제거하기 위한 bfs.
    queue<int> q;
    
    q.push(End);//마지막 정점에서 시작한다.
    while(!q.empty()){
        int nVertex = q.front();
        q.pop();
        for(int i=0; i<trace[nVertex].size(); i++){//해당 정점이 어디서 왔는지 찾는다.
            int vertex = trace[nVertex][i];//nVertex는 vertex에서 왔다.
            
            for(int i=0; i<graph[vertex].size(); i++){//graph에서 vertex에서 nVertex로 가는 간선을 찾는다.
                if(graph[vertex][i].first == nVertex)
                    graph[vertex][i].second = -1;//간선의 cost를 -1로 해준다. 다시 다익스트라를 실행할 때 이 간선은 제외된다.
            }
            
            q.push(vertex);//vertex는 어디서 왔는지 알아보기 위해 큐에 삽입한다.
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    while(true){
        cin >> n >> m;
        
        if(n==0 && m==0) break;
        
        for(int i=0; i<500; i++){//각 테스트 케이스마다 초기화 해줘야 한다.
            trace[i].clear();
            graph[i].clear();
        }
        
        int Start, End;
        cin >> Start >> End;
        
        for(int i=0; i<m; i++){
            int u,v,p;
            cin >> u >> v >> p;
            graph[u].push_back(make_pair(v,p));//u정점에서 v정점으로 갈 때 간선의 cost는 p다.
        }
        
        dijkstra(Start);//최단 경로를 찾는다.
        bfs(End);//최단 경로의 간선들을 제거한다.
        
        vector<int> result = dijkstra(Start);//거의 최단경로를 찾는다.
        
        if(result[End]==INF)//거의 최단경로를 못찾았을 때.
            cout << -1 << endl;
        else
            cout << result[End] << endl;
    }
    
    return 0;
}

//int conn_weight[500][500];
//int n, m;
//
//int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
//    cout.tie(NULL);
//
//    while(true){
//        cin >> n >> m;
//
//        if(n==0 && m==0) break;
//
//        memset(conn_weight, 0, sizeof(conn_weight));
//        vector<int> conn[500];
//        int Start, End;
//        cin >> Start >> End;
//
//        for(int i=0; i<m; i++){
//            int u,v,p;
//            cin >> u >> v >> p;
//            conn[u].push_back(v);
//            conn_weight[u][v]=p;
//        }
//
//        queue<tuple<int,int,vector<pair<int,int>>,map<int,int>>> q;
//        vector<pair<int,int>> tmpV;
//        map<int,int> tmpMap;
////        q.emplace(Start,0,tmpV,tmpMap);
//        q.push(make_tuple(Start,0,tmpV,tmpMap));
//        vector<pair<int,int>> min_weight;
//        int ans_weight = 999999999;
//        bool found = false;
//        while(!q.empty()){
//            vector<pair<int,int>> v;
//            map<int,int> Map;
//            int x, now_weight;
//            tie(x, now_weight, v, Map) = q.front();
//            q.pop();
//            if(x == End){
//                found=true;
//                if(now_weight == ans_weight){
//                    for(int i=0; i<v.size(); i++){
//                        min_weight.push_back(v[i]);
//                    }
//
//                }else if(now_weight < ans_weight){
//                    min_weight.clear();
//                    min_weight=v;
//                    ans_weight=now_weight;
//                }
//                continue;
//            }
//            if(found && now_weight>=ans_weight) continue;
//
//            for(int i=0; i<conn[x].size(); i++){
//                int next, next_weight;
//                next = conn[x][i];
//                next_weight = conn_weight[x][next];
//                if(Map.count(next)>0) continue;
//                vector<pair<int,int>> newV;
//                newV = v;
//                newV.push_back(make_pair(x,next));
//                map<int,int> newMap;
//                newMap=Map;
//                newMap[next]=1;
//                q.emplace(next, now_weight+next_weight, newV, newMap);
//            }
//        }
//        if(min_weight.size()==0){
//            cout << -1 << endl;
//            continue;
//        }
//        for(int i=0; i<min_weight.size(); i++){
//            int now, next;
//            tie(now, next) = min_weight[i];
//            conn_weight[now][next]=0;
//        }
//
//        queue<tuple<int,int,map<int,int>>> q2;
//        q2.emplace(Start,0,tmpMap);
//        ans_weight = 999999999;
//        found = false;
//        while(!q2.empty()){
//            int x, now_weight;
//            map<int,int> Map;
//            tie(x, now_weight, Map) = q2.front();
//            q2.pop();
//            if(x == End){
//                found=true;
//                if(now_weight < ans_weight)
//                    ans_weight = now_weight;
//            }
//            if(found && now_weight>=ans_weight) continue;
//
//            for(int i=0; i<conn[x].size(); i++){
//                int next, next_weight;
//                next = conn[x][i];
//                next_weight = conn_weight[x][next];
//                if(Map.count(next)>0) continue;
//                if(next_weight==0) continue;
//                if(next == End){
//                    q2.emplace(next, now_weight+next_weight, Map);
//                    continue;
//                }
//                map<int,int> newMap;
//                newMap = Map;
//                newMap[next]=1;
//                q2.emplace(next, now_weight+next_weight, Map);
//            }
//        }
//        if(ans_weight == 999999999)
//            cout << -1 << endl;
//        else
//            cout << ans_weight << endl;
//    }
//
//    return 0;
//}
