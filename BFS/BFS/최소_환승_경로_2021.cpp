//
//  최소_환승_경로_2021.cpp
//  BFS
//
//  Created by jiho park on 2020/02/21.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

#define endl "\n"
using namespace std;

vector<int> station[100001];//각 역에 몇호선이 있는지 저장하는 벡터.
vector<int> path[100001];//각 호선에 어느 역이 있는지 저장하는 벡터.
bool station_check[100001];//역에 대한 방문 배열.
bool line_check[100001];//호선에 대한 방문 배열.
int n,m;
int ans=999999999;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> m;
    for(int i=1; i<=m ;i++){
        int a;
        while(true){
            cin >> a;
            if(a==-1) break;
            path[i].push_back(a);//호선에 역 정보 저장.
            station[a].push_back(i);//역에 호선 정보 저장.
        }
    }
    int Start, End;
    cin >> Start >> End;
    if(Start == End){
        cout << 0;
        return 0;
    }
    queue<pair<int,int>> q;
    q.emplace(Start, 0);
    station_check[Start]=true;//시작 역에 대한 방문.
    bool found = false;
    while(!q.empty()){
        int st, cnt;
        tie(st, cnt) = q.front();
        q.pop();
        if(found && cnt >= ans) continue;//이미 목적지 역에 방문한 뒤에 환승횟수가 목적지 환승횟수 보다 큰 경우.
        for(int i=0; i<station[st].size(); i++){//해당 역에서 갈 수 있는 모든 호선 순회.
            int line = station[st][i];
            if(line_check[line]) continue;//이미 방문한 호선인 경우.
            line_check[line]=true;//호선 방문.
            for(int j=0; j<path[line].size(); j++){//해당 호선에서 갈 수 있는 모든 역 순회.
                if(station_check[path[line][j]]) continue;//이미 방문한 역인 경우.
                station_check[path[line][j]]=true;//역 방문.
                if(path[line][j]==End){//방문한 역이 목적지 역인 경우.
                    found=true;
                    if(cnt < ans)
                        ans = cnt;
                    continue;
                }
                if(station[path[line][j]].size()>1){//방문한 역에 갈 수 있는 다른 호선이 있는 경우.
                    q.emplace(path[line][j],cnt+1);//환승 횟수+1.
                }
            }
        }
    }
    if(ans == 999999999) cout << -1;//목적지역 까지 도달할 수 없는 경우.
    else cout << ans;
    
    return 0;
}
