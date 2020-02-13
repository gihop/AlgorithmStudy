//
//  중량제한_1939.cpp
//  BFS
//
//  Created by jiho park on 2020/02/13.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <queue>
#include <cstring>

#define endl "\n"
using namespace std;

//https://yabmoons.tistory.com/90 참고.
//이 문제를 꼭 다시 풀어보길 강력하게 추천한다.
//기존의 문제와 다르게 원래의 bfs로는 풀 수 가 없다.
//이미 큐에 들어갔던 정점이 다시 들어가야 하기 때문이다.
//그래서 미리 답을 정해놓고 탐색을 해야한다.
//답을 5라고 가정했을 때 bfs 경로가 1이라고 가정했을 때는 그 경로로 못갈 수도 있다.
//즉, 최단 간선을 갖는 경로가 아닌 경로의 간선 수는 더 많은 경로가 답인 경우가 있다.
//최단 거리를 찾는 것이 아닌 간선의 중량을 봐야하기 때문이다.
//하지만 이렇게만 했을 때 시간초과가 발생한다.
//주어지는 무게의 최대값은 1,000,000,000이기 때문에 1부터 1,000,000,000까지 다 검사할 수는 없다.
//그래서 추가로 이분탐색법이 필요하다. 하단에 이분탐색법 적용 전 코드를 주석처리 했다.
//문제의 최대 중량이 10이고 답이 5라면 1,2,3,4,5는 건널 수 있고 6,7,8,9,10은 건널 수 없기에 이분탐색법을 사용한다.

//int map[10001][10001];//메모리 낭비, 시간 낭비. 메모리 초과를 발생시킴. 배열 너무 큼. 이렇게 설계하면 틀림.
vector<pair<int,int>> v[10001];
int check[10001];
int n, m, max_weight;
int Start, End;
int ans;

bool bfs(int weight){
    queue<int> q;
    q.emplace(Start);
    check[Start]=true;
    while(!q.empty()){
        int city = q.front();
        q.pop();
        if(city == End) return true;//답이라고 가정한 중량 weight를 들고 End도시까지 운반할 수 있는 경우.
        
        for(int j=0; j<v[city].size(); j++){//현재 도시에서 갈 수 있는 도시 수 만큼 반복.
            int next_city, next_weight;//다음에 갈 도시와 연결된 다리의 중량.
            tie(next_city, next_weight) = v[city][j];
            if(check[next_city] || next_weight < weight) continue;//이미 방문한 도시이거나 예상한 중량보다 건너려는 다리의 중량이 더 작은 경우는 건너지 않는다.
            q.emplace(next_city);
            check[next_city]=true;
        }
    }
    
    return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m;
    
    for(int i=0; i<m; i++){
        int a,b,c;
        cin >> a >> b >> c;
        v[a].push_back(make_pair(b,c));//a에서 b로 갈 때 다리의 중량은 c이다.
        v[b].push_back(make_pair(a,c));
        if(c>max_weight)//입력된 다리의 중량 중 최대값을 찾는다.
            max_weight = c;
    }
    
    cin >> Start >> End;
    
    int low=0;//이분탐색법 부분.
    int high=max_weight;
    while(low<=high){
        memset(check, false, sizeof(check));
        int mid = (low+high)/2;
        if(bfs(mid)) low=mid+1;//mid 값은 가정된 답이다. 즉 mid값의 중량이 start에서 end까지 갈 수 있는지를 검사한다. 이분탐색법 적용 전에는 1~max_weight 까지 모든 값을 통과 할 수 있는지 검사해서 여기서 최대값을 찾았다. 하지만 이는 시간초과를 발생시킨다.
        else high = mid-1;
    }
    
    cout << high;
    
    return 0;
}

//이분탐색법을 뺀 풀이.
//vector<pair<int,int>> v[10001];
//int check[10001];
//int n, m, max_weight;
//int Start, End;
//int ans;
//
//bool bfs(int weight){
//    queue<int> q;
//    q.emplace(Start);
//    check[Start]=true;
//    while(!q.empty()){
//        int city = q.front();
//        q.pop();
//        if(city == End) return true;
//
//        for(int j=0; j<v[city].size(); j++){
//            int next_city, next_weight;
//            tie(next_city, next_weight) = v[city][j];
//            if(check[next_city] || next_weight < weight) continue;
//            q.emplace(next_city);
//            check[next_city]=true;
//        }
//    }
//
//    return false;
//}
//
//int main(){
//    ios_base::sync_with_stdio(false);
//    cin.tie(NULL);
//    cout.tie(NULL);
//
//    cin >> n >> m;
//
//    for(int i=0; i<m; i++){
//        int a,b,c;
//        cin >> a >> b >> c;
//        v[a].push_back(make_pair(b,c));
//        v[b].push_back(make_pair(a,c));
//        if(c>max_weight)
//            max_weight = c;
//    }
//
//    cin >> Start >> End;
//
//    int low=0;
//    int high=max_weight;
//    while(low<=high){
//        memset(check, false, sizeof(check));
//        int mid = (low+high)/2;
//        if(bfs(mid)) low=mid+1;
//        else high = mid-1;
//    }
//
//    cout << high;
//
//    return 0;
//}
