//
//  최단경로_1753.cpp
//  BFS
//
//  Created by jiho park on 2020/02/18.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

#define endl "\n"
using namespace std;

//다익스트라 활용 문제.
//다익스트라에서 꼭 필요한 것, graph, distance, priority_queue.

vector<pair<int,int>> graph[20001];
int V,E;
int INF=999999999;

vector<int> dijkstra(int Start){
    vector<int> distance(V+1, INF);//1번 부터 시작이기 때문에 V+1.
    priority_queue<pair<int,int>> pq;
    pq.emplace(0, Start);
    distance[Start] = 0;
    
    while(!pq.empty()){
        int vertex, weight;
        tie(weight, vertex) = pq.top();
        weight *= -1;//다시 양수로 바꿔줘야 함.
        pq.pop();
        
        if(weight > distance[vertex]) continue;//다익스트라에서 필수적인 부분.
        
        for(int i=0; i<graph[vertex].size(); i++){
            int nVertex, nWeight;
            tie(nVertex, nWeight) = graph[vertex][i];
            nWeight += weight;
            if(nWeight < distance[nVertex]){
                distance[nVertex] = nWeight;
                pq.emplace(-nWeight, nVertex);//음수로 weight를 넣어줘야 한다. priority_queue가 오름차순이기 때문.
            }
        }
    }
    
    return distance;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> V >> E;
    
    int Start;
    cin >> Start;
    
    for(int i=0; i<E; i++){
        int u,v,w;
        cin >> u >> v >> w;
        graph[u].push_back(make_pair(v,w));
    }
    
    vector<int> result = dijkstra(Start);
    
    for(int i=1; i<=V; i++){
        if(result[i]==INF)
            cout << "INF" << endl;
        else
            cout << result[i] << endl;
    }
    
    return 0;
}

