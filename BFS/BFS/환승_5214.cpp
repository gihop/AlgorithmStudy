//
//  환승_5214.cpp
//  BFS
//
//  Created by jiho park on 2020/02/22.
//  Copyright © 2020 jiho park. All rights reserved.
//

#include <iostream>
#include <tuple>
#include <vector>
#include <queue>

#define endl "\n"
using namespace std;

//최소 환승 경로 문제와 매우 유사한 문제.

vector<int> station[100001];//각 역에 어떤 호선이 있는지 저장한다.
vector<int> path[1001];//각 호선에 어떤 역이 있는지 저장한다.
bool check_st[100001];//역에 대한 방문 검사.
bool check_pt[1001];//호선에 대한 방문 검사.
int n, k, m;
int ans=999999999;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> n >> k >> m;
    for(int i=1; i<=m; i++){
        for(int j=0; j<k; j++){
            int st;
            cin >> st;
            station[st].push_back(i);//st역에 i호선이 지나고 있다.
            path[i].push_back(st);//i호선에 st역이 있다.
        }
    }
    if(n==1){//n이 1이면 답은 0.
        cout << 1;
        return 0;
    }
    check_st[1]=true;
    queue<pair<int,int>> q;//역의 번호와 방문하는 역의 갯수 저장.
    q.emplace(1,1);
    bool found = false;
    while(!q.empty()){
        int st, cnt;
        tie(st, cnt) = q.front();
        q.pop();
        if(found && cnt>=ans) continue;//이미 목적지 역을 찾은 상황에서 방문하는 역의 개수가 더 크거나 같은 경우는 갈필요가 없다.
        for(int i=0; i<station[st].size(); i++){//역을 지나는 모든 호선을 검사.
            int line = station[st][i];
            if(check_pt[line]) continue;//이미 방문한 호선인 경우.
            check_pt[line]=true;//호선 방문.
            for(int j=0; j<path[line].size(); j++){//호선에 있는 모든 역을 검사.
                int nSt = path[line][j];
                if(check_st[nSt]) continue;//이미 방문한 역인 경우.
                if(nSt == n){//목적지 역인 경우.
                    found=true;
                    if(cnt+1 < ans)
                        ans = cnt+1;
                    continue;
                }
                if(station[nSt].size()>1)//역에 호선이 두 개 이상인 경우 다른 호선도 검사해줘야 함.
                    q.emplace(nSt, cnt+1);
                check_st[nSt]=true;//역 방문.
            }
        }
    }
    if(ans == 999999999) cout << -1;//목적지 역에 도달할 수 없는 경우.
    else cout << ans;
    
    return 0;
}
